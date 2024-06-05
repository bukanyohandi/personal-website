import os
import io
import json
from torch.utils.data import Dataset, DataLoader
import numpy as np
from PIL import Image
import torch
from torch.autograd import Variable
import pdb
import torch.nn.functional as F
from sentence_transformers import SentenceTransformer

model = SentenceTransformer('sentence-transformers/all-MiniLM-L12-v2')

def process_caption(text):
    # Encode text and get model output
    embeddings = model.encode(text)
    ouput = np.expand_dims(embeddings, axis=0)
    return ouput

class Text2ImageDataset(Dataset):

    def __init__(self, dataset_dir):
        self.dataset_dir = dataset_dir
        with open(os.path.join(self.dataset_dir, 'descriptions.json'), 'r') as file:
          self.dataset = json.load(file)
        self.images_path = os.path.join(dataset_dir)

    def __len__(self):
        return len(self.dataset)

    def __getitem__(self, idx):
        if self.dataset is None:
            with open(os.path.join(self.dataset_dir, 'descriptions.json'), 'r') as file:
              self.dataset = json.load(file)

        item = self.dataset[idx]
        examples_class = self.dataset[idx]['text']
        examples_text = self.dataset[idx]['text']

        image_path = os.path.join(self.images_path, item['file_name'])
        right_image = Image.open(image_path).resize((128,128))
        right_embed = np.array(process_caption(examples_text), dtype=float)
        wrong_image = self.find_wrong_image(examples_class)

        right_image = self.validate_image(right_image)
        wrong_image = self.validate_image(wrong_image)

        sample = {
                'right_images': torch.FloatTensor(right_image),
                'right_embed': torch.FloatTensor(right_embed),
                'wrong_images': torch.FloatTensor(wrong_image)
                 }

        sample['right_images'] = sample['right_images'].sub_(127.5).div_(127.5)
        sample['wrong_images'] =sample['wrong_images'].sub_(127.5).div_(127.5)

        return sample

    def find_wrong_image(self, category):
        idx = np.random.randint(len(self.dataset))
        examples_class = self.dataset[idx]['class']
        _category = examples_class

        if _category != category:
          item = self.dataset[idx]
          image_path = os.path.join(self.images_path, item['file_name'])
          return Image.open(image_path).resize((128,128))

        return self.find_wrong_image(category)

    def validate_image(self, img):
        img = img.convert('RGB')
        img = np.array(img, dtype=float)
        if img.shape[2] == 4:
            img = img[:, :, :3]
        if len(img.shape) < 3:
            rgb = np.empty((64, 64, 3), dtype=np.float32)
            rgb[:, :, 0] = img
            rgb[:, :, 1] = img
            rgb[:, :, 2] = img
            img = rgb

        return img.transpose(2, 0, 1)
