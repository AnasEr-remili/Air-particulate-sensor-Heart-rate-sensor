from gps_class import GPS
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image, ImageDraw
import time

canvas = GPS(data_path='Brussel\gps_brussel.csv',
             map_path='Brussel\map7.png',
             points=(50.8438, 4.3617, 50.8204, 4.4080))

fijnstof = pd.read_csv (r'Brussel\fijnstof_brussel.csv')
hartslag = pd.read_csv (r'Brussel\hartslag_brussel.csv')
leeftijd = 22
max_hartslag = 220 - leeftijd

first_column = fijnstof.iloc[:, 0]
second_column = fijnstof.iloc[:, 1]
third_column = fijnstof.iloc[:, 2]

heart_val = hartslag.iloc[:, 0]
hartslag_col = hartslag.iloc[:, 0]

data_set = {"pm1": first_column , "hartslag": heart_val}
data_frame = pd.DataFrame(data_set)
data_frame["Coefficient pm1"] = data_frame["pm1"] * data_frame["hartslag"]

data_set2 = {"pm2_5": second_column , "hartslag": heart_val}
data_frame2 = pd.DataFrame(data_set2)
data_frame2["Coefficient pm2_5"] = data_frame2["pm2_5"] * data_frame2["hartslag"]

data_set3 = {"pm10": third_column , "hartslag": heart_val}
data_frame3 = pd.DataFrame(data_set3)
data_frame3["Coefficient pm10"] = data_frame3["pm10"] * data_frame3["hartslag"]

Coefficient_pm1 = data_frame.iloc[:, 2]
Coefficient_pm2_5 = data_frame2.iloc[:, 2]
Coefficient_pm10 = data_frame3.iloc[:, 2]

#GRENSWAARDES VOOR 20, 40 en 50
grenswaarde_20 = 20* max_hartslag
grenswaarde_40 = 40* max_hartslag
grenswaarde_50 = 50* max_hartslag

def checking_for_plot_PM1(Coefficient_pm1, grens_20, grens_40, grens_50, plot):
    for i in Coefficient_pm1:
        if i < grens_20:
            canvas.create_image(color=(0, 128, 0), width=5)    
        elif i >= grens_20 and i < grens_40:
            canvas.create_image(color=(255, 255, 0), width=5)
        elif i >= grens_40 and i < grens_50:
            canvas.create_image(color=(255, 0, 0), width=5)
    canvas.plot_map(output='save', title = "Afgerond parkour-PM1")

checking_for_plot_PM1(Coefficient_pm1, grenswaarde_20, grenswaarde_40, grenswaarde_50, canvas)

def checking_for_plot_PM2_5(Coefficient_pm2_5, grens20, grens40, grens50, plot):
    for i in Coefficient_pm2_5:
        if i < grens20:
            canvas.create_image(color=(0, 128, 0), width=5)    
        elif i >= grens20 and i < grens40:
            canvas.create_image(color=(255, 255, 0), width=5)
        elif i >= grens40 and i < grens50:
            canvas.create_image(color=(255, 0, 0), width=5)
    canvas.plot_map(output='save', title = "Afgerond parkour-PM2.5")

#checking_for_plot_PM2_5(Coefficient_pm2_5, grenswaarde_20, grenswaarde_40, grenswaarde_50, canvas)

def checking_for_plot_PM10(Coefficient_pm10, grens_20, grens_40, grens_50, plot):

    for i in Coefficient_pm10:
        if i < grens_20:
           canvas.create_image(color=(0, 128, 0), width=5)    
        elif i >= grens_20 and i < grens_40:
            canvas.create_image(color=(255, 255, 0), width=5)
        elif i >= grens_40 and i < grens_50:
            canvas.create_image(color=(255, 0, 0), width=5)
    canvas.plot_map(output='save', title = "Afgerond parkour-PM10")

#checking_for_plot_PM10(Coefficient_pm10, grenswaarde_20, grenswaarde_40, grenswaarde_50, canvas)

