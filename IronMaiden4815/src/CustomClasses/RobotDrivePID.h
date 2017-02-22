#ifndef ROBOTDRIVEPID_H
#define ROBOTDRIVEPID_H

#include "RobotDrive.h"
#include "PIDOutput.h"
#include "WPILib.h"

class RobotDrivePID: public PIDOutput, public RobotDrive {

public:
	enum class PIDSrcType {
		kDisplacement, kRotation, kRate
	};

	RobotDrivePID(int leftMotorChannel, int rightMotorChannel, PIDSrcType src =
			PIDSrcType::kDisplacement);
	RobotDrivePID(int frontLeftMotorChannel, int rearLeftMotorChannel,
			int frontRightMotorChannel, int rearRightMotorChannel,
			PIDSrcType src = PIDSrcType::kDisplacement);
	RobotDrivePID(frc::SpeedController* leftMotor, frc::SpeedController* rightMotor,
			PIDSrcType src = PIDSrcType::kDisplacement);
	RobotDrivePID(frc::SpeedController& leftMotor, frc::SpeedController& rightMotor,
			PIDSrcType src = PIDSrcType::kDisplacement);
	RobotDrivePID(frc::SpeedController* frontLeftMotor,
			frc::SpeedController* rearLeftMotor, frc::SpeedController* frontRightMotor,
			frc::SpeedController* rearRightMotor, PIDSrcType src = PIDSrcType::kDisplacement);
	RobotDrivePID(frc::SpeedController& frontLeftMotor,
			frc::SpeedController& rearLeftMotor, frc::SpeedController& frontRightMotor,
			frc::SpeedController& rearRightMotor, PIDSrcType src = PIDSrcType::kDisplacement);
	RobotDrivePID(std::shared_ptr<frc::SpeedController> leftMotor,
			std::shared_ptr<frc::SpeedController> rightMotor, PIDSrcType src =
					PIDSrcType::kDisplacement);
	RobotDrivePID(std::shared_ptr<frc::SpeedController> frontLeftMotor,
			std::shared_ptr<frc::SpeedController> rearLeftMotor,
			std::shared_ptr<frc::SpeedController> frontRightMotor,
			std::shared_ptr<frc::SpeedController> rearRightMotor, PIDSrcType src =
					PIDSrcType::kDisplacement);
	virtual ~RobotDrivePID() = default;

	PIDSrcType GetPIDSrcType() {return pidSource;};
	void setPIDSrcType(PIDSrcType src) { pidSource = src;};

	void PIDWrite(double output) override;

private:
	enum PIDSrcType pidSource;
};

#endif

