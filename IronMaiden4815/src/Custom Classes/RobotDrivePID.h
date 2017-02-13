#ifndef ROBOTDRIVEPID_H
#define ROBOTDRIVEPID_H

#include "RobotDrive.h"
#include "PIDOutput.h"

class RobotDrivePID: public PIDOutput, public RobotDrive{
private:
	PIDSrcType pidSource;

public:
	enum class PIDSrcType{kDisplacement, kRotation, kRate};

	RobotDrivePID(int leftMotorChannel, int rightMotorChannel, 
		PIDSrcType src=kDisplacement);
	RobotDrivePID(int frontLeftMotorChannel, int rearLeftMotorChannel, 
		int frontRightMotorChannel, int rearRightMotorChannel, 
		PIDSrcType src=kDisplacement);
	RobotDrivePID(SpeedController* leftMotor, SpeedController* rightMotor, 
		PIDSrcType src=kDisplacement);
	RobotDrivePID(SpeedController& leftMotor, SpeedController& rightMotor, 
		PIDSrcType src=kDisplacement);
	RobotDrivePID(SpeedController* frontLeftMotor, SpeedController* rearLeftMotor, 
		SpeedController* frontRightMotor, SpeedController* rearRightMotor, 
		PIDSrcType src=kDisplacement);
	RobotDrivePID(SpeedController& frontLeftMotor, SpeedController& rearLeftMotor, 
		SpeedController& frontRightMotor, SpeedController& rearRightMotor, 
		PIDSrcType src=kDisplacement);
	RobotDrivePID(std::shared_ptr<SpeedController> leftMotor,
             std::shared_ptr<SpeedController> rightMotor,
             PIDSrcType src=kDisplacement);
	RobotDrivePID(std::shared_ptr<SpeedController> frontLeftMotor,
             std::shared_ptr<SpeedController> rearLeftMotor,
             std::shared_ptr<SpeedController> frontRightMotor,
             std::shared_ptr<SpeedController> rearRightMotor,
             PIDSrcType src=kDisplacement);
	virtual ~RobotDrivePID() = default;

	PIDSrcType GetPIDSrcType();
	void setPIDSrcType();

	void PIDWrite(double output) override;
};

#endif