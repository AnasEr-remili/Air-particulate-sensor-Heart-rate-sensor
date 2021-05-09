import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image, ImageDraw
from matplotlib.patches import Patch
from matplotlib.lines import Line2D

class GPS(object):

    def  __init__(self, data_path, map_path, points):

        self.data_path = data_path
        self.points = points
        self.map_path = map_path

        self.result_image = Image
        self.x_grens = []
        self.y_grens = []

    def plot_map(self, output='save', save_as='resultMap.png', title = ''):
        self.grens_coordinaten()
        legend_elements = [Line2D([0], [0], color='g', lw=4, label='Goed: fijnstof < 20 µg/m³',),
        Line2D([0], [0], color='y', lw=4, label='Matig: fijnstof >= 20 µg/m³ maar =< 40 µg/m³'),
        Line2D([0], [0], color='r', lw=4, label='Slecht: fijnstof >= 40 µg/m³ maar < 50 µg/m³' )] 
        
        
        fig, axis1 = plt.subplots(figsize=(20, 20))
        axis1.imshow(self.result_image)
        axis1.set_title(title, fontdict={'fontsize': 20, 'fontweight': 'medium'} )
        axis1.set_xlabel('Breedtegraad')
        axis1.xaxis.label.set_size(20)
        axis1.set_ylabel('Lengtegraad')
        axis1.yaxis.label.set_size(20)
        axis1.grid()

        # Create the figure
        axis1.legend(handles=legend_elements, loc='lower right')
        if output == 'save':
            plt.savefig(save_as)
        else:
            plt.show()

    def create_image(self, color, width=2):
    
        data = pd.read_csv(self.data_path, names=['LATITUDE', 'LONGITUDE'], sep=',')

        self.result_image = Image.open(self.map_path, 'r')
        img_points = []
        gps_data = tuple(zip(data['LATITUDE'].values, data['LONGITUDE'].values))
        for d in gps_data:
            x1, y1 = self.scale_to_img(d, (self.result_image.size[0], self.result_image.size[1]))
            img_points.append((x1, y1))
        draw = ImageDraw.Draw(self.result_image)
        draw.line(img_points, fill=color, width=width)

    def scale_to_img(self, lat_lon, h_w):
  
        old = (self.points[2], self.points[0])
        new = (0, h_w[1])
        y = ((lat_lon[0] - old[0]) * (new[1] - new[0]) / (old[1] - old[0])) + new[0]
        old = (self.points[1], self.points[3])
        new = (0, h_w[0])
        x = ((lat_lon[1] - old[0]) * (new[1] - new[0]) / (old[1] - old[0])) + new[0]
        return int(x), h_w[1] - int(y)

    def grens_coordinaten(self):

        self.x_grens = map(
            lambda x: round(x, 4),
            np.linspace(self.points[1], self.points[3], num=7))
        y_grens = map(
            lambda x: round(x, 4),
            np.linspace(self.points[2], self.points[0], num=8))
        self.y_grens = sorted(y_grens, reverse=True)
