import cv2

# cv2.imshow(" ", cv2.imread("1.jpg"))
# cv2.waitKey()

image = cv2.imread("1.jpg")
cv2.imwrite("hello.png", image)
