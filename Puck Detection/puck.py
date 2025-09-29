import cv2
import numpy as np

# Define puck color range in HSV (adjust for your puck color)
lower_puck = np.array([0, 0, 0])   # Adjust these values
upper_puck = np.array([180, 255, 50])  # Adjust these values

# Start capturing video
cap = cv2.VideoCapture(0)  # Change index if using an external camera

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Convert to HSV color space
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Create a mask to filter out the puck
    mask = cv2.inRange(hsv, lower_puck, upper_puck)

    # Find contours of the puck
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    for contour in contours:
        # Get bounding circle
        (x, y), radius = cv2.minEnclosingCircle(contour)
        center = (int(x), int(y))
        radius = int(radius)

        # Draw the detected puck
        if radius > 10:  # Ignore small noise
            cv2.circle(frame, center, radius, (0, 255, 0), 2)
            cv2.putText(frame, "Puck", (center[0] - 20, center[1] - 20), 
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

    # Show the processed frame
    cv2.imshow("Puck Detection", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
