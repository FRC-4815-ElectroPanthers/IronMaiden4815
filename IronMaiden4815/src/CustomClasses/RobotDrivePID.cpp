#include "RobotDrivePID.h"
#include "WPILib.h"

RobotDrivePID::RobotDrivePID(int leftMotorChannel, int rightMotorChannel, 
		PIDSrcType src):RobotDrive(leftMotorChannel, rightMotorChannel),
		pidSource(src){}

RobotDrivePID::RobotDrivePID(int frontLeftMotorChannel, int rearLeftMotorChannel, 
		int frontRightMotorChannel, int rearRightMotorChannel, 
		PIDSrcType src):RobotDrive(frontLeftMotorChannel, rearLeftMotorChannel,
		frontRightMotorChannel, rearRightMotorChannel), 
		pidSource(src){}

RobotDrivePID::RobotDrivePID(frc::SpeedController* leftMotor, frc::SpeedController* rightMotor,
		PIDSrcType src):RobotDrive(leftMotor, rightMotor),
		pidSource(src){}

RobotDrivePID::RobotDrivePID(frc::SpeedController& leftMotor, frc::SpeedController& rightMotor,
		PIDSrcType src):RobotDrive(leftMotor, rightMotor),
		pidSource(src){}

RobotDrivePID::RobotDrivePID(frc::SpeedController* frontLeftMotor, frc::SpeedController* rearLeftMotor,
		frc::SpeedController* frontRightMotor, frc::SpeedController* rearRightMotor,
		PIDSrcType src):RobotDrive(frontLeftMotor, rearLeftMotor,
		frontRightMotor, rearRightMotor), 
		pidSource(src){}

RobotDrivePID::RobotDrivePID(frc::SpeedController& frontLeftMotor, frc::SpeedController& rearLeftMotor,
		frc::SpeedController& frontRightMotor, frc::SpeedController& rearRightMotor,
		PIDSrcType src):RobotDrive(frontLeftMotor, rearLeftMotor,
		frontRightMotor, rearRightMotor), 
		pidSource(src){}

RobotDrivePID::RobotDrivePID(std::shared_ptr<frc::SpeedController> leftMotor,
             std::shared_ptr<frc::SpeedController> rightMotor,
             PIDSrcType src):RobotDrive(leftMotor, rightMotor),
		pidSource(src){}

RobotDrivePID::RobotDrivePID(std::shared_ptr<frc::SpeedController> frontLeftMotor,
             std::shared_ptr<frc::SpeedController> rearLeftMotor,
             std::shared_ptr<frc::SpeedController> frontRightMotor,
             std::shared_ptr<frc::SpeedController> rearRightMotor,
             PIDSrcType src):RobotDrive(frontLeftMotor, rearLeftMotor,
		frontRightMotor, rearRightMotor), 
		pidSource(src){}

/*
 *
PIDSrcType RobotDrivePID::GetPIDSrcType() const {
	return pidSource;
}

void RobotDrivePID::setPIDSrcType(PIDSrcType src){
	pidSource = src;
}
*/
void RobotDrivePID::PIDWrite(double output){
	if(pidSource == PIDSrcType::kRotation){
		TankDrive(output, -output);
	}else{
		TankDrive(output, output);
	}
}

