#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw = LiveWindow::GetInstance();
	Joystick *stick;
	Talon *fl, *fr, *bl, *br;

	VictorSP *gearRight, *gearLeft;
	CameraServer *cam;

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

		cam = CameraServer::GetInstance();

		cam->StartAutomaticCapture();
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
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		float x = stick->GetRawAxis(0);
		float y = stick->GetRawAxis(1);

		if(x < .3 && x > -.3)
			x = 0;
		if(y < .3 && y > -.3)
			y = 0;


		float Lout = y - x;
		float Rout = y + x;

		std::cout << "Lout: " << Lout << std::endl;
		std::cout << "Rout: " << Rout << std::endl;

		if(stick->GetRawButton(1)){
			gearRight->Set(y);
			gearLeft->Set(-y);
		}else{
			fl->Set(-Lout);
			fr->Set(Rout);
			bl->Set(-Lout);
			br->Set(Rout);
		}
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
