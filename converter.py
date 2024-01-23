from PIL import Image
import os

path = "/Users/jakekasper/ML/Datasets/MNIST/Data"
dest_path = "/Users/jakekasper/ML/Datasets/MNIST/BMPData"

for split in os.listdir(path):
    if split[0] == '.':
        continue

    splitpath = os.path.join(path, split)
    for cls in os.listdir(splitpath):
        if cls[0] == '.':
            continue
        
        classpath = os.path.join(splitpath, cls)
        
        for file in os.listdir(classpath):
            filepath = os.path.join(classpath, file)

            im = Image.open(filepath)
            os.makedirs(os.path.join(dest_path, split, cls), exist_ok=True)
            im.save(os.path.join(dest_path, split, cls, f"{file[:-4]}.bmp"), format='bmp')