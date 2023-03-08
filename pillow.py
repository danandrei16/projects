import zipfile

from PIL import Image
import pytesseract
import cv2 as cv
import numpy as np


print('aaa')
# loading the face detection classifier
face_cascade = cv.CascadeClassifier('readonly/haarcascade_frontalface_default.xml')

# the rest is up to you!
imageDict = {}
#files = [] # filenames

zip = zipfile.ZipFile('readonly/small_img.zip')
#zip = zipfile.ZipFile('readonly/images.zip', mode='r')

for elem in zip.infolist():
    imageDict[elem.filename] = [Image.open(zip.open(elem.filename))]
    #files.append(elem.filename)
    
for fileName in imageDict.keys():
    imageDict[fileName].append(pytesseract.image_to_string(imageDict[fileName][0]).replace('\n', ''))
    
    if 'Mark' in imageDict[fileName][1]:
        print('Results found in file ' + fileName)
        
        try:
            # storing boxes of faces
            faces = face_cascade.detectMultiScale(np.array(imageDict[fileName][0]), 1.35, 4).tolist()
            imageDict[fileName].append(faces)
            
            facesList = []
            
            for x, y, weight, height in imageDict[fileName][2]:
                facesList.append(imageDict[fileName][0].crop(x, y, x + weight, y + height))
            
            contact = Image.new(imageDict[fileName][0].mode, (550, 110 * int(np.ceil(len(facesList) / 5))))
            x, y = 0, 0
            
            for face in faceList:
                face.thumbnail((110, 110))
                contact.paste(face, (x, y))
                
                if contact.width == x + 110:
                    x, y = 0, y + 110
                else:
                    x = x + 110
            
            display(contact)
            
        except:
            print('But there were no faces in that file!')