import os

TITLE_ART = """
  ______     _______.  ______  _  _     __   ___     ___      .______   .___________..______   
 /      |   /       | /      || || |   /_ | |__ \   / _ \     |   _  \  |           ||   _  \  
|  ,----'  |   (----`|  ,----'| || |_   | |    ) | | | | |    |  |_)  | `---|  |----`|  |_)  | 
|  |        \   \    |  |     |__   _|  | |   / /  | | | |    |   ___/      |  |     |   ___/  
|  `----.----)   |   |  `----.   | |    | |  / /_  | |_| |    |  |          |  |     |  |      
 \______|_______/     \______|   |_|    |_| |____|  \___/     | _|          |__|     | _|      
                                                                                               
                                                              
"""

INPUT_FILE_DIRECTORY = "inputs"
OUTPUT_FILE_DIRECTORY = "outputs"

def list_all_files(directory, extension):
    """
    List all files under path
    """
    files = get_files_with_extension(directory, extension)
    for file in files:
        print(file)

def get_files_with_extension(directory, extension):
    """
    Get all files end with specified extension under directory
    """
    files = []
    for file in os.listdir(directory):
        if file.endswith(extension):
            files.append(file)
    return sorted(files)

def input_file_names_to_file_path(user_in_files_str, in_files_all):
    user_in_files = user_in_files_str.split()
    file_paths = []
    message = ''
    for file in user_in_files:
        if file in in_files_all:
            file_paths.append(os.path.join(os.path.join(os.getcwd(), INPUT_FILE_DIRECTORY), file))
        else:
            file_con = file + '.in'
            if file_con in in_files_all:
                file_paths.append(os.path.join(os.path.join(os.getcwd(), INPUT_FILE_DIRECTORY), file_con))
            else:
                message += f'{file} '
    if message:
        message = 'Input ' + message + 'Not Exist'
    return file_paths, message

def read_file(file):
    """
    Read all lines in file 
    Store the data in a list of lines
    where each line is splited to list of words   
    """
    with open(file, 'r') as f:
        lines = f.readlines()
    return [line.strip().split() for line in lines]

def write_to_file(file, data, mode='w'):
    """
    Write data into file
    Default mode: 'w'
    """
    with open(file, mode) as f:
        f.write(data)

if __name__ == "__main__":
    list_all_files("./inputs")