# https://learnopencv.com/object-tracking-using-opencv-cpp-python/
import cv2
import sys

tracker = cv2.TrackerCSRT_create()
video = cv2.VideoCapture(0)
if not video.isOpened():
    print ("Could not open video")
    sys.exit()

ok, frame = video.read()
if not ok:
    print ("Cannot read video")
    sys.exit()

bbox = cv2.selectROI("Select starting point", frame, fromCenter=False)
tracker.init(frame, bbox)

while True:
    timer = cv2.getTickCount()
    ok, frame = video.read()
    if not ok:
        break



    
    ok, bbox = tracker.update(frame)
    


    if ok:
        p1 = (int(bbox[0]), int(bbox[1]))
        p2 = (int(bbox[0] + bbox[2]), int(bbox[0] + bbox[3]))
        cv2.rectangle(frame, p1, p2, (255, 0, 0), 2, 1)
    else:
        cv2.putText(frame, "Tracking failure :(", (100, 80), cv2.FONT_HERSHEY_SIMPLEX, 0.75,(0,0,255),2)

    fps = cv2.getTickFrequency() / (cv2.getTickCount() - timer)

    cv2.putText(frame, "FPS : " + str(int(fps)), (100,50), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (50,170,50), 2);
    cv2.imshow("Tracking", frame)

    k = cv2.waitKey(1)


    if k & 0xff == 27:
        break