import cv2
import matplotlib.pyplot as plt

# Load the image
img = cv2.imread('download.jpg')

B, G, R = cv2.split(img)
# Corresponding channels are separated

cv2.imshow("original", img)
cv2.waitKey(0)

cv2.imshow("blue", B)
cv2.waitKey(0)

cv2.imshow("Green", G)
cv2.waitKey(0)

cv2.imshow("red", R)
cv2.waitKey(0)

cv2.destroyAllWindows()

# Rgb_img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
# plt.imshow(Rgb_img)
# plt.waitforbuttonpress()
# plt.close('all')

# cv2.imshow("",img)
# print("Высота:"+str(img.shape[0]))
# print("Ширина:" + str(img.shape[1]))
# print("Количество каналов:" + str(img.shape[2]))
# cv2.waitKey(0)

