
#include "RobotDrivePID.h"

RobotDrivePID::RobotDrivePID(int leftMotorChannel, int rightMotorChannel, 
		PIDSrcType src=PIDSrcType::kDisplacement):RobotDrive(leftMotorChannel, rightMotorChannel),
		pidSource(src){}

RobotDrivePID::RobotDrivePID(int frontLeftMotorChannel, int rearLeftMotorChannel, 
		int frontRightMotorChannel, int rearRightMotorChannel, 
		PIDSrcType src=PIDSrcType::kDisplacement):RobotDrive(frontLeftMotorChannel, rearLeftMotorChannel,
		frontRightMotorChannel, rearRightMotorChannel), 
		pidSource(src){}

RobotDrivePID::RobotDrivePID(SpeedController* leftMotor, SpeedController* rightMotor, 
		PIDSrcType src=PIDSrcType::kDisplacement):RobotDrive(leftMotor, rightMotor),
		pidSource(src){}

RobotDrivePID::RobotDrivePID(SpeedController& leftMotor, SpeedController& rightMotor, 
		PIDSrcType src=PIDSrcType::kDisplacement):RobotDrive(leftMotor, rightMotor),
		pidSource(src){}

RobotDrivePID::RobotDrivePID(SpeedController* frontLeftMotor, SpeedController* rearLeftMotor, 
		SpeedController* frontRightMotor, SpeedController* rearRightMotor, 
		PIDSrcType src=PIDSrcType::kDisplacement):RobotDrive(frontLeftMotor, rearLeftMotor,
		frontRightMotor, rearRightMotor), 
		pidSource(src){}

RobotDrivePID::RobotDrivePID(SpeedController& frontLeftMotor, SpeedController& rearLeftMotor, 
		SpeedController& frontRightMotor, SpeedController& rearRightMotor, 
		PIDSrcType src=PIDSrcType::kDisplacement):RobotDrive(frontLeftMotor, rearLeftMotor,
		frontRightMotor, rearRightMotor), 
		pidSource(src){}

RobotDrivePID::RobotDrivePID(std::shared_ptr<SpeedController> leftMotor,
             std::shared_ptr<SpeedController> rightMotor, 
             PIDSrcType src=PIDSrcType::kDisplacement):RobotDrive(leftMotor, rightMotor),
		pidSource(src){}

RobotDrivePID::RobotDrivePID(std::shared_ptr<SpeedController> frontLeftMotor,
             std::shared_ptr<SpeedController> rearLeftMotor,
             std::shared_ptr<SpeedController> frontRightMotor,
             std::shared_ptr<SpeedController> rearRightMotor,
             PIDSrcType src=PIDSrcType::kDisplacement):RobotDrive(frontLeftMotor, rearLeftMotor,
		frontRightMotor, rearRightMotor), 
		pidSource(src){}

PIDSrcType RobotDrivePID::GetPIDSrcType(){
	return pidSource;
}

void RobotDrivePID::setPIDSrcType(PIDSrcType src){
	pidSource = src;
}

void RobotDrivePID::PIDWrite(double output){
	if(pidSource == PIDSrcType::kRotation){
		TankDrive(output, -output);
	}else{
		TankDrive(output, output);
	}
}

