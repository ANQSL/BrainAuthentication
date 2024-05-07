import sys

from calculate import Calculate
from communicate import Communication
sys.path.append("D:/project/BrainAuthentication/Calculate/identity_recognition")
if __name__ == "__main__":

    communicate = Communication(32, 250)
    calculate = Calculate()
    communicate.start()
    calculate.start()
    print("计算启动")
    # while (True):
    #     pass
