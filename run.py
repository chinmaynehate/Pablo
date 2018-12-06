import pablo as arm


if __name__=="__main__":
    # x=float(input("Enter Target X:"))
    # y=float(input("Enter Target Y:"))
    # z=float(input("Enter Target Z:"))

    x=1
    y=1
    z=1
    writeLegIndex = 0

    t1,t2,t3 = arm.getInverse(x,y,z)
    input("Press Any Key to Write")
    arm.goToXY(x,y,z,writeLegIndex)

