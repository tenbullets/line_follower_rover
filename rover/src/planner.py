import rospy
import cv2
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
from std_msgs.msg import String

bridge = CvBridge()
command_pub = rospy.Publisher("motor_commands", String)

def is_black(val):
  return val < 95

def plan(left, right):
  print(left, right)

  command = "STOP"

  if is_black(left) and is_black(right):
    command = "GO"

  if is_black(left) and not is_black(right):
    command = "LEFT"

  if not is_black(left) and is_black(right):
    command = "RIGHT"

  print(command)

  command_pub.publish(command)



def imgCallBack(data):
  cv_image = bridge.imgmsg_to_cv2(data, "bgr8")

  gray_img = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)

  plan(gray_img[700][265], gray_img[700][535])

  # print(cv_image.shape)

  gray_img = cv2.line(gray_img, (265,700), (535,700), 0, 6)
  cv2.imshow("Raw Image", gray_img)
  cv2.waitKey(3)


def main():
  print("Hey Universe!")

  rospy.init_node('my_planner_node')
  img_sub = rospy.Subscriber("/camera/image_raw", Image, imgCallBack)
  rospy.spin()

if __name__ == "__main__":
  main()

