



#include "Kinematics.h"
#include "MatrixUtils.h"

//jacobian and matrix values 

int var1;
int var2;
int var3;
int var4;
int var5;

int somepin = 3;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

    Kinematics kin(3);
    MatrixUtils mat_utils;

    kin.add_joint_axis(0, 0,  1,  4, 0,    0);
    kin.add_joint_axis(0, 0,  0,  0, 1,    0);
    kin.add_joint_axis(0, 0, -1, -6, 0, -0.1);

    kin.add_initial_end_effector_pose(-1, 0,  0, 0,
                                       0, 1,  0, 6,
                                       0, 0, -1, 2,
                                       0, 0,  0, 1);

    float desired_transform[4][4] = {
        {0, 1,  0,     -5},
        {1, 0,  0,      4},
        {0, 0, -1, 1.6858},
        {0, 0,  0,      1}
    };

    float jac[6][3];
    float jac_t[6][3];
    float AA_t[6][6];
    float A_tA[3][3];
    float pinv[3][6];

    float joint_angles_0[3] = {1.0, 2.5, 3};
    float joint_angles[3];

    kin.inverse((float*)desired_transform, (float*)jac, (float*)pinv, (float*)jac_t, (float*)AA_t, (float*)A_tA, joint_angles_0, 0.01, 0.001, 20, joint_angles);
    mat_utils.print_matrix(joint_angles, 1, N, "Joint angles");
}

pinMode(somepin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(somepin,HIGH);
  

}
