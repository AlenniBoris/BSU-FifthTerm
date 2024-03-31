import time

import cv2
# image = cv2.imread('download.jpg')
# image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
#
#
# mask = numpy.zeros((image.shape[:2]), dtype=numpy.uint8)
# mask = cv2.cvtColor(mask, cv2.COLOR_BGR2RGB)
#
#
# cv2.circle(mask, (290, 290), 80, (255, 255, 255), -1)
#
# masked = cv2.bitwise_and(image, mask)
# cv2.imshow("Mask applied", masked)
#
# cv2.waitKey(0)
# cv2.destroyAllWindows()


# 14.09

# image = cv2.imread('download.jpg')
# cv2.imshow("Original", image)
#
# height, width = image.shape[:2]
#
# rotation_matrix = cv2.getRotationMatrix2D((width / 2, height / 2), 45, 1.0)
#
# new_width = int(width / 2)
# new_height = int(height / 2)
#
# resized = cv2.resize(image, (new_width, new_height))
#
# angleMatrix = numpy.float32([[1, numpy.tan(numpy.radians(45)), 0],[0, 1, 0]])
#
# resized = cv2.warpAffine(resized, rotation_matrix, (width, height))
# resized = cv2.warpAffine(resized, angleMatrix, (width, height))
#
# cv2.imshow("Resized", resized)
#
# cv2.waitKey(0)
# cv2.destroyAllWindows()

# 21.09

# Взять из одной картинки сделать 2 прямоуг-ка : на черно-бел и цветной

# image = cv2.imread('download.jpg')
# rectangle = image[0:500, 0:500]
# image1 = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
# blackAndWhite = image1[0:500, 0:500]
# cv2.imshow("Original", image)
# cv2.imshow("Rectangle", rectangle)
# cv2.imshow("Black-white picture", blackAndWhite)
# cv2.waitKey(0)
# cv2.destroyAllWindows()


#

#
# rectangle = cv2.imread('download.jpg',  0)
# kernel = numpy.ones((5,5))
# kernel_size = kernel.shape[0]
# padding = kernel_size // 2
# filtered = numpy.zeros_like(rectangle, dtype = np.float32)
# height, width = rectangle.shape
#
# for i in range(padding, height - padding):
#     for j in range(padding, width - padding):
#                 patch = rectangle[i - padding: i + padding + 1, j - padding: j + padding + 1]
#                 result = np.sum(patch * kernel)
#                 filtered[i, j] = result
#
# filtered = (filtered - np.min(filtered)) / (np.max(filtered) - np.min(filtered)) * 255
# filtered = filtered.astype(np.uint8)
#
# cv2.imshow("rectangle", rectangle)
# cv2.imshow("filtered", filtered)
# cv2.waitKey(0)

# 28/09/23

# def contrast(value):
#     contrastImage = cv2.convertScaleAbs(image, alpha=value, beta=0)
#     cv2.imshow("image", contrastImage)
#
#
# def brightness(value):
#     brightImage = cv2.convertScaleAbs(image, alpha=1, beta=value)
#     cv2.imshow('image', brightImage)
#
# def gamma(value):
#     gamma = value / 100.0
#     gammaImage = np.power(image / 255.0, gamma)
#     gammaImage = (gammaImage * 255).astype(np.uint8)
#     cv2.imshow('image', gammaImage)
#
#
# image = cv2.imread('download.jpg')
#
# histogram = cv2.calcHist([image], [0], None, [256], [0, 256])
# plt.figure()
# plt.title('Гистограмма изображения')
# plt.xlabel('Яркость пикселей')
# plt.ylabel('Частота')
# plt.plot(histogram, color='red')
# plt.xlim([0, 256])
#
# cv2.namedWindow("image")
# cv2.imshow("image", image)
# cv2.createTrackbar("Contrast", "image", 0,10,contrast)
# cv2.createTrackbar('Brightness', 'image', 0, 255, brightness)
# cv2.createTrackbar('Gamma', 'image', 100, 200, gamma)
#
# plt.show()
#
# cv2.waitKey(0)
# cv2.destroyAllWindows()

#5/10/2023

# import pydicom as dicom
# import matplotlib.pylab as plt
#
# image = dicom.dcmread('white.dcm')
#
# pixels = 110*image.pixel_array
#
# display_min = 12000  # Minimum value for the display range
# display_max = 14000  # Maximum value for the display range
# # Plot histogram
# plt.hist(pixels.flatten(), bins=256, range=(display_min, display_max), color='c')
# plt.xlabel('Pixel Intensity')
# plt.ylabel('Frequency')
# plt.title('Pixel Intensity Histogram')
#
# plt.imshow(pixels)
# plt.show()

#12/10/23

# import cv2
# from deconvolution import Deconvolution
# from PIL import Image
#
# img = Image.open("image003.jpg")
#
#
# decimg1 = Deconvolution(image=img, basis=[[1,0,0], [0,0,0]])
#
# layer1, _ = decimg1.out_images(mode=[1,2])
#
#
# layer1.save("r.jpg")
#
# decimg2 = Deconvolution(image=img, basis=[[0,0,1], [90/255,93/255,128/255]])
#
# layer2,_ = decimg2.out_images(mode=[1,2])
# layer2.save("b.jpg")

# import cv2
# import numpy as np
#
#
# def remove_color(image, color):
#     hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
#
#     mask = np.zeros_like(hsv_image[:, :, 0])
#
#     target_color_hsv = cv2.cvtColor(np.uint8([[target_color]]), cv2.COLOR_BGR2HSV)[0][0]
#     target_color_lower = np.array([target_color_hsv[0] - 10, 50, 50])
#     target_color_upper = np.array([target_color_hsv[0] + 10, 255, 255])
#
#     mask = cv2.inRange(hsv_image, target_color_lower, target_color_upper)
#
#     result = cv2.bitwise_and(image, image, mask=mask)
#
#     return result
#
#
# image = cv2.imread("image003.jpg")
#
# target_color = [49,43,144]
#
# redStamp = remove_color(image, target_color)
#
# cv2.imshow("Original Image", image)
# cv2.imwrite("RedStamp.jpg", redStamp)
#
# cv2.waitKey(0)
# cv2.destroyAllWindows()

#30/11/23

# import cv2
# import numpy as np
# import random
#
# image_path = 'sample10.jpg'
# image = cv2.imread(image_path)
#
# gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
#
# _, binary_image = cv2.threshold(gray_image, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
#
# edged = cv2.Canny(binary_image, 30, 200)
# contours, hierarchy = cv2.findContours(edged,
#     cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
#
# for i, contour in enumerate(contours):
#     color = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
#     cv2.drawContours(image, [contour], -1, color, thickness=cv2.FILLED)
#
# cv2.imshow('Original Image', image)
# cv2.imshow('Processed Image', binary_image)
#
# cv2.waitKey(0)
# cv2.destroyAllWindows()

# import cv2 as cv
# import os
# import numpy as np
#
# def harris_detect(image):
#     operatedImage = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
#     operatedImage = np.float32(operatedImage)
#     dest = cv.cornerHarris(operatedImage, 4, 5, 0.13)
#     dest = cv.dilate(dest, None)
#     image[dest > 0.01 * dest.max()] = [0, 0, 255]
#
# def rotate(image,angle):
#     height, width = image.shape[:2]
#     center = (width / 2, height / 2)
#     rotation_matrix = cv.getRotationMatrix2D(center, angle, 1.0)
#     rotated_image = cv.warpAffine(image, rotation_matrix, (width, height))
#     return rotated_image
#
# def find_match(template, search):
#     detected_template = harris_detect(template)
#     detectrd_search = harris_detect(search)
#
#
# image = cv.imread("finger.jpg")

# cv.imshow('Image', image)

# for angle in range(0,361,5):
#     rotated = rotate(image, angle)
#     rotatedIm = rotate(image, angle)
#     harris_detect(rotatedIm)
#     path = os.path.join("rotates_star", f"rotated_{angle}.jpg")
#     cv.imwrite(path, rotatedIm)
#     image = rotated
#     cv.imshow('Rotation', rotatedIm)
#     cv.waitKey(100)

# template = cv.imread("fingerprints.jpg")
# firstFinger = cv.imread("fp2.jpg")
# secondFinger = cv.imread("fp2.jpg")
#
# first_detected = find_match(template, firstFinger)
# second_detected = find_match(template, secondFinger)
#
# path = os.path.join("finger_detection", f"detected_first.jpg")
# cv.imwrite(path, first_detected)
# path = os.path.join("finger_detection", f"detected_second.jpg")
# cv.imwrite(path, second_detected)
#
# cv.waitKey(0)
# cv.destroyAllWindows()

# import cv2
#
# image_path = "roads.jpeg"
# original_image = cv2.imread(image_path)
#
# cv2.imshow("Without contours", original_image)
#
# gray_image = cv2.cvtColor(original_image, cv2.COLOR_BGR2GRAY)
#
# # Применение бинаризации для выделения объекта
# _, thresh = cv2.threshold(gray_image, 128, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)
# # Поиск контуров
# contours, _ = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
#
# # Рисуем контуры
# cv2.drawContours(original_image, contours, -1, (0, 255, 0), 2)
#
# # Инициализация переменной для хранения площади объекта
# size = 0
#
# # Перебор найденных контуров
# for contour in contours:
#     # Вычисление площади контура и добавление к общей площади
#     area = cv2.contourArea(contour)
#     size += area
#     x, y, w, h = cv2.boundingRect(contour)
#     cv2.putText(original_image, str(area), (x, y),
#                 cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 1)
#
# # Вывод результата
# print("Площадь объекта: {} пикселей".format(size))
#
# cv2.imshow("With contours", original_image)
#
# cv2.waitKey(0)
# cv2.destroyAllWindows()




import cv2
def apply_dilatation(img):
    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(5,5))
    img = cv2.dilate(img,kernel,iterations = 4)
    return img

img = cv2.imread('23.jpg')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

_,binarized = cv2.threshold(gray, 0, 255, cv2.THRESH_OTSU)

binarized = 255 - binarized

dilatated = apply_dilatation(binarized)

cv2.imshow('binarized', binarized)
cv2.imshow('dilatated', dilatated)


image = cv2.imread('23.jpg')
gray1 = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

_, thresh = cv2.threshold(gray1, 0, 255, cv2.THRESH_OTSU+cv2.THRESH_BINARY_INV)
contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

result = image.copy()

cv2.drawContours(result, contours, -1, (0, 255, 0), 3)
cv2.fillPoly(result, contours, (0, 0, 255))

cv2.imshow('Result', result)

cv2.waitKey(0)
cv2.destroyAllWindows()
