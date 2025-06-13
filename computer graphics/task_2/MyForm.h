#pragma once

namespace Diev {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	float fish[] = {
		//��������
		1.f, 1.f, 2.f, 2.f,
		2.f, 2.f, 3.f, 1.f,
		3.f, 1.f, 2.f, 0.f,
		2.f, 0.f, 1.f, 1.f,

		0.f, 12.f, 1.f, 13.f,
		1.f, 13.f, 2.f, 12.f,
		2.f, 12.f, 1.f, 11.f,
		1.f, 11.f, 0.f, 12.f,

		2.f, 14.f, 3.f, 15.f,
		3.f, 15.f, 4.f, 14.f,
		4.f, 14.f, 3.f, 13.f,
		3.f, 13.f, 2.f, 14.f,

		2.f, 16.f, 3.f, 17.f,
		3.f, 17.f, 4.f, 17.f,
		4.f, 17.f, 5.f, 16.f,
		5.f, 16.f, 5.f, 15.f,
		5.f, 15.f, 4.f, 14.f,
		4.f, 14.f, 3.f, 14.f,
		3.f, 14.f, 2.f, 15.f,
		2.f, 15.f, 2.f, 16.f,

		23.f, 8.f, 25.f, 10.f,
		25.f, 10.f, 27.f, 8.f,
		27.f, 8.f, 25.f, 6.f,
		25.f, 6.f, 23.f, 8.f,

		25.f, 12.f, 24.f, 13.f,
		24.f, 13.f, 25.f, 14.f,
		25.f, 14.f, 26.f, 13.f,
		26.f, 13.f, 25.f, 12.f,

		16.f, 16.f, 17.f, 17.f,
		17.f, 17.f, 18.f, 16.f,
		18.f, 16.f, 17.f, 15.f,
		17.f, 15.f, 16.f, 16.f,

		15.f, 16.f, 17.f, 16.f,
		17.f, 16.f, 18.f, 15.f,
		18.f, 15.f, 18.f, 13.f,
		18.f, 13.f, 17.f, 12.f,
		17.f, 12.f, 15.f, 12.f,
		15.f, 12.f, 14.f, 13.f,
		14.f, 13.f, 14.f, 15.f,
		14.f, 15.f, 15.f, 16.f,

		//��������
		5.f, 6.f, 4.f, 7.f,
		4.f, 7.f, 4.f, 8.f,
		4.f, 8.f, 5.f, 9.f,
		5.f, 9.f, 6.f, 9.f,
		6.f, 9.f, 7.f, 8.f,
		7.f, 8.f, 7.f, 7.f,
		7.f, 7.f, 6.f, 6.f,
		6.f, 6.f, 5.f, 6.f,

		6.f, 6.f, 6.f, 7.f,
		6.f, 7.f, 5.f, 7.f,
		5.f, 7.f, 5.f, 6.f,

		//������
		1.f, 7.f, 2.f, 9.f,
		2.f, 9.f, 3.f, 10.f,
		3.f, 10.f, 5.f, 11.f,
		5.f, 11.f, 8.f, 11.f,
		8.f, 11.f, 12.f, 10.f,
		12.f, 10.f, 16.f, 8.f,
		16.f, 8.f, 17.f, 6.f,
		17.f, 6.f, 9.f, 2.f,
		9.f, 2.f, 5.f, 3.f,
		5.f, 3.f, 2.f, 5.f,
		2.f, 5.f, 3.f, 6.f,
		3.f, 6.f, 2.f, 7.f,
		2.f, 7.f, 1.f, 7.f,

		8.f, 11.f, 10.f, 9.f,
		10.f, 9.f, 8.f, 7.f,
		8.f, 7.f, 10.f, 5.f,
		10.f, 5.f, 8.f, 3.f,
		8.f, 3.f, 9.f, 2.f,

		//������ �������
		9.f, 4.f, 16.f, 4.f,
		16.f, 4.f, 17.f, 3.f,
		17.f, 3.f, 17.f, 1.f,
		17.f, 1.f, 15.f, 0.f,
		15.f, 0.f, 12.f, 1.f,
		12.f, 1.f, 9.f, 4.f,

		9.f, 4.f, 17.f, 3.f,
		9.f, 4.f, 17.f, 2.f,
		9.f, 4.f, 17.f, 1.f,
		9.f, 4.f, 15.f, 0.f,

		//������� �������
		5.f, 11.f, 8.f, 16.f,
		8.f, 16.f, 8.f, 14.f,
		6.f, 11.f, 8.f, 14.f,
		8.f, 14.f, 9.f, 15.f,
		9.f, 15.f, 9.f, 13.f, 
		7.f, 11.f, 10.f, 14.f,
		10.f, 14.f, 10.f, 12.f,
		8.f, 11.f, 10.f, 12.f,
		10.f, 12.f, 11.f, 13.f,
		10.f, 10.5f, 11.f, 11.f,
		11.f, 11.f, 11.f, 13.f,
		11.f, 11.f, 12.f, 12.f,
		12.f, 12.f, 12.f, 10.f,
		12.f, 10.f, 13.f, 11.f,
		13.f, 11.f, 13.f, 9.5f,

	    //�����
		17.f, 6.f, 16.f, 8.f,
	    16.f, 8.f, 14.f, 9.f,
		14.f, 9.f, 19.f, 11.f,
		19.f, 11.f, 20.f, 13.f, 
		20.f, 13.f, 21.f, 14.f, 
		21.f, 14.f, 23.f, 15.f,
		23.f, 15.f, 24.f, 15.f,
		24.f, 15.f, 23.f, 14.f, 
		23.f, 14.f, 22.f, 11.f,
		22.f, 11.f, 21.f, 9.f,
		21.f, 9.f, 20.f, 8.f, 
		20.f, 8.f, 21.f, 7.f,
		21.f, 7.f, 22.f, 5.f,
		22.f, 5.f, 23.f, 2.f,
		23.f, 2.f, 24.f, 1.f,
		24.f, 1.f, 23.f, 1.f,
		23.f, 1.f, 21.f, 2.f,
		21.f, 2.f, 20.f, 3.f,
		20.f, 3.f, 19.f, 5.f, 
		19.f, 5.f, 17.f, 6.f

	};
	unsigned int arrayLength_fish = sizeof(fish) / sizeof(float);
	float Vx_fish = 27.f;
	float Vy_fish = 18.f;
	float aspectFig_fish = Vx_fish / Vy_fish;

	float rabbit[] = {
		// ������
		0.5f,3.f,1.f,4.5f, // �� ����� ���� ����� �� ���
		1.f,4.5f,0.5f,6.f, // ����� ��� ����� ����� �����
		0.5f,6.f,0.5f, 7.5f, // ����� ��� �����
		0.5f, 7.5f,1.f,8.f, // ����� ��� ���� �����
		1.f,8.f,1.5f,8.f, // ����� ��� ���� ��������
		1.5f,8.f,2.f,7.5f, // ����� ��� ���� ������
		2.f,7.5f,1.5f, 6.f, // ����� ��� ������ ������ ����
		1.5f, 6.f,1.5f,4.5f, // ����� ��� ������ �� �������
		1.5f,4.5f,3.f,4.5f, // �������
		3.f,4.5f,3.f,6.f, // ������ ��� ����� ����� �����
		3.f,6.f,2.5f,7.5f, // ������ ��� �����
		2.5f,7.5f,3.f,8.f, // ������ ��� ���� �����
		3.f,8.f,3.5f,8.f, // ������ ��� ���� ��������
		3.5f,8.f,4.f,7.5f, // ������ ��� ���� ������
		4.f,7.5f,4.f,6.f, // ������ ��� ������ ����
		4.f,6.f,3.5f,4.5f, // ������ ��� ������
		3.5f,4.5f,4.f,3.f, // �� ������� ��� ���� �� ����
		4.f,3.f,3.5f,1.5f, // ������ �����
		3.5f,1.5f,2.5f,1.f, // ���������� ������
		2.5f,1.f,2.f,1.f, // ���������� �����
		2.f,1.f,1.f,1.5f, // ���������� �����
		1.f,1.5f,0.5f,3.f, // ����� �����
		// ��������
		4.f,3.f,5.5f,3.5f, // ����� �� ������ ������
		5.5f,3.5f,7.f,3.5f, // ����� ����
		7.f,3.5f,7.5f,2.5f, // ����� ������ �� ������
		7.5f,2.5f,8.f,2.5f, // ����� ������
		8.f,2.5f,8.f,2.f, // ����� ������
		8.f,2.f,7.5f,2.f, // ����� ��� ������ ������
		7.5f,2.f,7.5f,0.5f, // ������ ���� ������ ������ ����
		7.5f,0.5f,6.5f,0.5f, // ������ ���� ���
		6.5f,0.5f,6.5f,1.f, // ������ ���� �����
		6.5f,1.f,6.f,1.f, // ����� ������ ���
		6.f,1.f,6.f,0.5f, // ����� ������ ���� ������
		6.f,0.5f,5.f,0.5f, // ����� ������ ���� ���
		5.f,0.5f,5.f,1.f, // ����� ������ ���� �����
		5.f,1.f,4.f,1.f, // ����� ������� � ��������� ������
		4.f,1.f,4.f,0.5f, // ������ �������� ���� ������
		4.f,0.5f,3.f,0.5f, // ������ �������� ���� ���
		3.f,0.5f,3.f,1.f, // ������ �������� ���� �����
		3.f,1.f,2.5f,1.f, // ����� �������� ���
		2.5f,1.f,2.5f,0.5f, // �������� ���� ������
		2.5f,0.5f,1.5f,0.5f, // �������� ���� ���
		1.5f,0.5f,1.5f,1.25f, // �������� ���� �����
		// ����� ����
		1.5f,3.5f,1.5f,3.f, // ����� ���� ����� ������ ����
		1.5f,3.f,2.f,3.f, // ����� ���� ���
		2.f, 3.f,2.f,3.5f, // ����� ���� ������
		2.f,3.5f,1.5f,3.5f, // ����� ���� ����
		// ������ ����
		2.5f,3.5f,2.5f,3.f, // ������ ���� �����
		2.5f,3.f,3.f, 3.f, // ������ ���� �����
		3.f,3.f,3.f,3.5f, // ������ ���� ������
		3.f,3.5f,2.5f,3.5f, // ������ ���� ������
		// ����� ��������
		1.f,5.5f,1.f,7.f, // ����� ����� ��������
		3.5f,5.5f,3.5f,7.f, // ������ ����� ��������
		// ���
		2.f,2.5f,2.5f,2.5f, // ��� ������
		2.5f,2.5f,2.25f,2.f, // ��� ������
		2.25f,2.f,2.f,2.5f // ��� �����
	};
	unsigned int arrayLength_rabbit = sizeof(rabbit) / sizeof(float);
	float Vx_rabbit = 8.5f;
	float Vy_rabbit = 8.5f;
	float aspectFig_rabbit = Vx_rabbit / Vy_rabbit;


	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(379, 322);
			this->DoubleBuffered = true;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: bool keepAspectRatio;
	private: bool switchImage;
	private: int backgroundColor;
	private: bool epilephsia;
	private: Random^ rnd = gcnew Random();
	private: int R = 255, G = 255, B = 255;
	private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		Graphics^ g = e->Graphics;

		switch (backgroundColor) {
			case 0: g->Clear(Color::White); break;
			case 1:	g->Clear(Color::Red); break;
			case 2:	g->Clear(Color::Green); break;
			case 3:	g->Clear(Color::Blue); break;
			default: break;
		}

		if (epilephsia)
			g->Clear(Color::FromArgb(255, R, G, B));

		Pen^ blackPen = gcnew Pen(Color::Black, 2);

		float Wx = ClientRectangle.Width;
		float Wy = ClientRectangle.Height;
		float aspectForm = Wx / Wy;

		float aspectFig, Vx, Vy, arrayLength;
		float* lines;
		if (switchImage) {
			lines = fish;
			arrayLength = sizeof(fish) / sizeof(float);
			aspectFig = aspectFig_fish;
			Vx = Vx_fish;
			Vy = Vy_fish;
		}
		else {
			lines = rabbit;
			arrayLength = sizeof(rabbit) / sizeof(float);
			aspectFig = aspectFig_rabbit;
			Vx = Vx_rabbit;
			Vy = Vy_rabbit;
		}

		float Sx, Sy;
		if (keepAspectRatio) {
			Sx = Sy = (aspectFig < aspectForm) ? Wy / Vy : Wx / Vx;
		}
		else {
			Sx = Wx / Vx;
			Sy = Wy / Vy;
		}
		float Ty = Sy * Vy;

		for (int i = 0; i < arrayLength; i += 4) {
			g->DrawLine(blackPen, Sx * lines[i], -Sy * lines[i + 1] + Ty, 
								  Sx * lines[i + 2], -Sy * lines[i + 3] + Ty);
		}

		if (epilephsia) {
			R = rnd->Next(255);
			G = rnd->Next(255);
			B = rnd->Next(255);
			Refresh();
		}

	}

	private: System::Void MyForm_Resize(System::Object^  sender, System::EventArgs^  e) {
		Refresh();
	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		keepAspectRatio = true;
		switchImage = true;
		backgroundColor = 0;
		epilephsia = false;
	}

	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {

		case Keys::M:
			keepAspectRatio = !keepAspectRatio;
			break;

		case Keys::N:
			switchImage = !switchImage;
			break;

		case Keys::C:
			epilephsia = false;
			backgroundColor = (backgroundColor + 1) % 4;
			break;

		case Keys::X:
			backgroundColor = 0;
			epilephsia = !epilephsia;
			break;

		default:
			break;
		}
		Refresh();
	}

	};
}
