#pragma once

namespace Diev {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	vec2 Vc;
	vec2 V;
	vec2 Vc_work, V_work;

	mat3 T;
	mat3 initT;

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
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog;
	protected:


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
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->DefaultExt = L"txt";
			this->openFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
			this->openFileDialog->Title = L"Открыть файл";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(379, 322);
			this->DoubleBuffered = true;
			this->KeyPreview = true;
			this->Margin = System::Windows::Forms::Padding(4);
			this->MinimumSize = System::Drawing::Size(205, 150);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: int backgroundColor;
	private: bool epilephsia;
	private: float left = 30, right = 100, top = 20, bottom = 50;
			 float minX = left, maxX; 
			 float minY = top, maxY; 
			 float Wcx = left, Wcy; 
			 float Wx, Wy;

			 int numXsect = 5, numYsect = 5, numZsect = 5;

	private: System::Void rectCalc() {
		maxX = ClientRectangle.Width - right;
		maxY = ClientRectangle.Height - bottom;
		Wcy = maxY;
		Wx = maxX - left;
		Wy = maxY - top;
	}

	private: System::Void worldRectCalc() {
		Vc_work = normalize(T * vec3(Vc, 1.f));
		V_work = mat2(T) * V;
	}

	private: float f(float x) {
		return tan(x);
	}

	private: bool f_exists(float x, float delta) {
		return fabs(2.f * acos(cos(x)) - Math::PI) > delta;
	}

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

		Pen^ rectPen = gcnew Pen(Color::Black, 2);
		g->DrawRectangle(rectPen, left, top, Wx, Wy);

		Pen^ gridPen = gcnew Pen(Color::Black, 1);
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);
		System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 8);

		float gridStep_x = Wx / numXsect;
		float grid_dX = V_work.x / numXsect;

		float tick_x = Vc_work.x;
		for (int i = 0; i <= numXsect; i++) {

			float tmpXCoord_v = Wcx + i * gridStep_x;

			g->DrawLine(gridPen, tmpXCoord_v, minY, tmpXCoord_v, maxY);

			if (i > 0 && i < numXsect)
				g->DrawString(tick_x.ToString("F4"), drawFont, drawBrush, tmpXCoord_v-20.f, maxY);

			tick_x += grid_dX;
		}

		float gridStep_y = Wy / numYsect;
		float grid_dY = V_work.y / numYsect;

		float tick_y = Vc_work.y;
		for (int i = 0; i <= numYsect; i++) {

			float tmpYCoord_g = Wcy - i * gridStep_y;

			g->DrawLine(gridPen, minX, tmpYCoord_g, maxX, tmpYCoord_g);

			if (i > 0 && i < numYsect)
				g->DrawString(tick_y.ToString("F4"), drawFont, drawBrush, maxX, tmpYCoord_g - 20.f);

			tick_y += grid_dY;
		}


		Pen^ pen = gcnew Pen(Color::Blue, 1);

		float deltaX = V_work.x / Wx;

		bool hasStart;
		vec2 start;
		float x, y;
		start.x = Wcx;
		x = Vc_work.x;

		hasStart = f_exists(x, deltaX);
		if (hasStart) {
			y = f(x);
			start.y = Wcy - (y - Vc_work.y) / V_work.y * Wy;
		}

		while (start.x < maxX) {
			vec2 end;
			bool hasEnd;

			float deltaY;
			float red, green, blue;

			end.x = start.x + 1.f;
			x += deltaX;

			hasEnd = f_exists(x, deltaX);
			if (hasEnd) {
				y = f(x);

				deltaY = (y - Vc_work.y) / V_work.y;
				end.y = Wcy - deltaY * Wy;
			}
			
			vec2 tmpEnd = end;
			bool visible = hasStart && hasEnd && clip(start, end, minX, minY, maxX, maxY);

			if (visible) {

				if (deltaY > 1.f) deltaY = 1.f;
				if (deltaY < 0.f) deltaY = 0.f;
				green = 510 * deltaY;
				if (deltaY < 0.5) {
					blue = 255.f - green;
					red = 0.f;
				}
				else {
					blue = 0.f;
					red = green - 255.f;
					green = 510.f - green;
				}

				pen->Color = Color::FromArgb(red, green, blue);
				g->DrawLine(pen, start.x, start.y, end.x, end.y);
			}

			start = tmpEnd;
			hasStart = hasEnd;
		}

		if (epilephsia) {
			R = rnd->Next(255);
			G = rnd->Next(255);
			B = rnd->Next(255);
			Refresh();
		}

	}

	private: System::Void MyForm_Resize(System::Object^  sender, System::EventArgs^  e) {
		rectCalc();
		Refresh();
	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		backgroundColor = 0;
		epilephsia = false;

		initT = mat3(1.f);
		T = initT;

		Vc = vec2(-2.f, -2.f);
		V = vec2(4.f, 4.f);

		rectCalc();
		worldRectCalc();
	}

	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		
		float centerX = Vc_work.x + V_work.x / 2;
		float centerY = Vc_work.y + V_work.y / 2;

		switch (e->KeyCode) {

		case Keys::A: 
			T = translate(-V_work.x / Wx, 0.f) * T;
			break;

		case Keys::D:
			T = translate(V_work.x / Wx, 0.f) * T;
			break;

		case Keys::W:
			T = translate(0.f, -V_work.x / Wx) * T;
			break;

		case Keys::S:
			T = translate(0.f, V_work.x / Wx) * T;
			break;

		case Keys::Z: 
			T = translate(-centerX, -centerY) * T;
			T = scale(1.1f) * T;
			T = translate(centerX, centerY) * T;
			break;

		case Keys::X:
			T = translate(-centerX, -centerY) * T;
			T = scale(0.9f) * T;
			T = translate(centerX, centerY) * T;
			break;

		case Keys::T:
			T = translate(-centerX, -centerY) * T;
			T = scale(1.1f, 1.f) * T;
			T = translate(centerX, centerY) * T;
			break;

		case Keys::G:
			T = translate(-centerX, -centerY) * T;
			T = scale(0.9f, 1.f) * T;
			T = translate(centerX, centerY) * T;
			break;

		case Keys::Y:
			T = translate(-centerX, -centerY) * T;
			T = scale(1.f, 1.1f) * T;
			T = translate(centerX, centerY) * T;
			break;

		case Keys::P:
			T = translate(-centerX, -centerY) * T;
			T = rotate(0.01f) * T;
			T = translate(centerX, centerY) * T;
			break;

		case Keys::H:
			T = translate(-centerX, -centerY) * T;
			T = scale(1.f, 0.9f) * T;
			T = translate(centerX, centerY) * T;
			break;

		case Keys::D1:
			numXsect++;
			break;

		case Keys::D2:
			numXsect--;
			if (numXsect <= 2) numXsect = 2;
			break;

		case Keys::D3:
			numYsect++;
			break;

		case Keys::D4:
			numYsect--;
			if (numYsect <= 2) numYsect = 2;
			break;

		case Keys::B:
			epilephsia = false;
			backgroundColor = (backgroundColor + 1) % 4;
			break;

		case Keys::N:
			backgroundColor = 0;
			epilephsia = !epilephsia;
			break;

		case Keys::Escape:
			T = initT;
			break;

		default:
			break;
		}

		worldRectCalc();
		Refresh();
	}
};
}
