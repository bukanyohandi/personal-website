import gradio as gr
import numpy as np
import torch
import torchvision.transforms as transforms
from sentence_transformers import SentenceTransformer, util
import json
import os
import matplotlib.pyplot as plt
import random
import torch
import torch.nn as nn
from generatorModel import Generator

def load_embedding(model):
    # Load your model and other components here
    with open(os.path.join("descriptions.json"), 'r') as file:
        dataset = json.load(file)
    
    classes = [e["text"] for e in dataset]
    embeddings_list = {cls: model.encode(cls, convert_to_tensor=True) for cls in classes}
    return embeddings_list, classes

def generate_image(caption):
    noise_dim = 16
    results = [(util.pytorch_cos_sim(model.encode(caption, convert_to_tensor=True), embeddings[cls]).item(), cls) for cls in classes]
    sorted_results = sorted(results, key=lambda x: x[0], reverse=True)[:5]

    threshold = 0.40
    coeff = 0.89

    if sorted_results[0][0] <= threshold:
        caption = sorted_results[0][1]
        results = [(util.pytorch_cos_sim(model.encode(caption, convert_to_tensor=True), embeddings[cls]).item(), cls) for cls in classes]
        sorted_results = sorted(results, key=lambda x: x[0], reverse=True)[:5]

    if sorted_results[0][0] >= 0.99:
        coeff = 0.85

    last_score = sorted_results[0][0]
    filtered_results = []
    for score, cls in sorted_results:
        if score >= last_score * coeff:
            filtered_results.append((score, cls))
            last_score = score
        else:
            break

    items = [cls for score, cls in filtered_results]
    probabilities = [score for score, cls in filtered_results]
    sampled_item = random.choices(items, weights=probabilities, k=1)[0]

    noise = torch.randn(1, noise_dim, 1, 1, device=device)  # Adjust noise_dim if different
    fake_images = generator(noise, embeddings[sampled_item].unsqueeze(0).unsqueeze(0))
    img = fake_images.squeeze(0).permute(1, 2, 0).cpu().detach().numpy()
    img = (img - img.min()) / (img.max() - img.min())
    return img

noise_dim = 16
embed_dim = 384
embed_out_dim = 256
device = 'cpu'

generator = Generator(channels=3, embed_dim=embed_dim, noise_dim=noise_dim, embed_out_dim=embed_out_dim).to(device)

# Path to .pth file and load the weights
gen_weight = 'generator_20240421_3.pth'
weights_gen = torch.load(gen_weight, map_location=torch.device(device))
generator.load_state_dict(weights_gen)

model = SentenceTransformer('sentence-transformers/all-MiniLM-L12-v2')

embeddings, classes = load_embedding(model)


iface = gr.Interface(fn=generate_image,
                     inputs=gr.Textbox(lines=2, placeholder="Enter Caption Here..."),
                     outputs=gr.Image(type="numpy", height=256, width=256),
                     title="CUHK Shenzhen Building Text-to-Image Generation",
                     description="Enter a caption of some specific building in CUHK-Shenzhen to generate an image.."
                    )

iface.launch(debug=True)
