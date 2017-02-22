#include "WPILib.h"
#include "CustomClasses/RobotDrivePID.h"
#include "CANTalon.h"
#define PI 3.14159
#define P_ENCODER 0.5
#define I_ENCODER 0
#define D_ENCODER 0

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw = LiveWindow::GetInstance();
	Joystick *stick;

	Talon *fl, *fr, *bl, *br;
	VictorSP *gearRight, *gearLeft;
	CANTalon *climbingTalon;
	RobotDrivePID *drive;

	Encoder *driveEncoder;
	ADXRS450_Gyro *driveGyro;
	CameraServer *cam;

	PIDController *driveController;
	bool driven;
	Timer *time;
	//SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;

	void RobotInit()
	{
		//chooser = new SendableChooser();
		//chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		//chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
	    //SmartDashboard::PutData("Auto Modes", chooser);

		stick = new Joystick(0);
		fl = new Talon(0);
		bl = new Talon(1);
		fr = new Talon(2);
		br = new Talon(3);

		gearLeft = new VictorSP(4);
		gearRight = new VictorSP(5);
		climbingTalon = new CANTalon(1);

		driveEncoder = new Encoder(1,2);
		driveGyro = new ADXRS450_Gyro();

		driveEncoder->SetDistancePerPulse(PI/8192); // ft/s
		driveEncoder->SetMinRate(0.005);

		drive = new RobotDrivePID(fl, bl, fr, br, RobotDrivePID::PIDSrcType::kDisplacement);

		cam = CameraServer::GetInstance();
		cam->StartAutomaticCapture();

		driveController = new PIDController(P_ENCODER,
											I_ENCODER,
											D_ENCODER,
											driveEncoder,
											drive);
	}


	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
	 * If using the SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit()
	{
	//	autoSelected = *((std::string*)chooser->GetSelected());
		//std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;
        driven = false;
        time = new Timer();


		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}
	}

	void AutonomousPeriodic()
	{
		if(time->Get() > 5.0 ){
			driven = true;
			fr->Set(0.0);
			bl->Set(0.0);
			fl->Set(0.0);
			br->Set(0.0);
			time->Stop();
			time->Reset();
			//Custom Auto goes here
		}
		if(time->Get() < 5.0 && !driven){
			fl->Set(0.5);
			bl->Set(0.5);
			fr->Set(0.5);
			br->Set(0.5);
			//Default Auto goes here
		}

		driveController->SetSetpoint(6.0);
		driveController->Enable();
	}

	void TeleopInit()
	{
		driveController->Disable();

	}

	void TeleopPeriodic()
	{
		float x = stick->GetRawAxis(0);
		float y = stick->GetRawAxis(1);
		float strafe = stick->GetRawAxis(2);

		if(x < .1 && x > -.1)
			x = 0;
		if(y < .1 && y > -.1)
			y = 0;
		if(strafe < .1 && strafe > -.1)
			strafe = 0;

		/*
		float Lout = y - x;
		float Rout = y + x;

		std::cout << "Lout: " << Lout << std::endl;
		std::cout << "Rout: " << Rout << std::endl;
		*/

		if(stick->GetRawButton(1)){
			gearRight->Set(y);
			gearLeft->Set(-y);
		}
		else if(stick->GetRawButton(3)){
			//Climber is only one directional
			if(y<0){
				y = -y;
			}
			climbingTalon->Set(y);
		}
		else{
			climbingTalon->Set(0);

			/*
			fl->Set(-Lout);
			fr->Set(Rout);
			bl->Set(-Lout);
			br->Set(Rout);
			*/

			drive->MecanumDrive_Cartesian(strafe, y, x);
		}
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
