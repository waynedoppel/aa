#pragma once
#include <windows.h>
#include <windowsx.h>
#using <System.dll>
#using <System.Core.dll>
#include "MemoryUtils.h"
#include <iostream>
#include "Globals.h"
#include "ActionCore.h"
#include "InjectESP.h"



#define WM_NCLBUTTONDOWN 0x00A1
#define HTCAPTION 2
#define WDA_EXCLUDEFROMCAPTURE 0x00000011
#define WDA_NONE 0x00000000
#define GWL_EXSTYLE -20
#define WS_EX_TOOLWINDOW 0x00000080



namespace BraveDllFull {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::Threading::Tasks;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for form2
	/// </summary>
	public ref class form2 : public System::Windows::Forms::Form
	{
	public:
		form2(void)
		{
			InitializeComponent();			pictureBox2->Padding = System::Windows::Forms::Padding(6);
			pictureBox3->Padding = System::Windows::Forms::Padding(6);
			pictureBox4->Padding = System::Windows::Forms::Padding(6);

			ArredondarPictureBox(pictureBox2);
			ArredondarPictureBox(pictureBox3);
			ArredondarPictureBox(pictureBox4);

			AplicarEstiloBotao(button8);
			AplicarEstiloBotao(AimlegitClick);
			AplicarEstiloBotao(AimNeck);
			AplicarEstiloBotao(button1);
			AplicarEstiloBotao(button5);
			AplicarEstiloBotao(button6);
			AplicarEstiloBotao(button7);
			ArredondarBotao(button8);
			ArredondarBotao(AimlegitClick);
			ArredondarBotao(AimNeck);
			ArredondarBotao(button1);
			ArredondarBotao(button5);
			ArredondarBotao(button6);
			ArredondarBotao(button7);

			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &form2::form2_MouseDown);

			// STREAM MODE inicializado ativado
			if (streamModeAtivado) {
				HWND hWnd = static_cast<HWND>(this->Handle.ToPointer());
				SetWindowDisplayAffinity(hWnd, WDA_EXCLUDEFROMCAPTURE);
				ToggleVisual(button7, true);
			}

			// HIDE TASKBAR também ativado separadamente
			this->ShowInTaskbar = false;


			this->DoubleBuffered = true; // suaviza flicker
			//this->Paint += gcnew PaintEventHandler(this, &form2::DrawParticles);
			this->ClientSize = System::Drawing::Size(544, 360);


			//Funções Automaticas

			OcultarDoAltTab();


			//FUNÇÃO PRECISION 
			precisionAtivado = false;
			AimNeck->BackColor = Color::IndianRed;
			AimNeck->ForeColor = Color::White;

			// Painéis internos ao panel4
			panel4->Size = System::Drawing::Size(514, 320);

			// Posicionamento padrão para todos os painéis
			panel2->Parent = panel4;
			panel5->Parent = panel4;
			panel7->Parent = panel4;

			System::Drawing::Point posicaoPadrao = System::Drawing::Point(110, 10);
			System::Drawing::Size tamanhoPadrao = System::Drawing::Size(414, 320);

			panel2->Location = posicaoPadrao;
			panel5->Location = posicaoPadrao;
			panel7->Location = posicaoPadrao;

			panel2->Size = tamanhoPadrao;
			panel5->Size = tamanhoPadrao;
			panel7->Size = tamanhoPadrao;


			// Linha vertical de separação
			System::Windows::Forms::Panel^ panelSeparador = gcnew System::Windows::Forms::Panel();
			panelSeparador->BackColor = System::Drawing::Color::FromArgb(60, 60, 60);
			panelSeparador->Location = System::Drawing::Point(105, 10);
			panelSeparador->Size = System::Drawing::Size(1, 300);
			this->panel4->Controls->Add(panelSeparador);

			// Mostrar só o panel2 no início
			panel2->Visible = true;
			MarcarSelecionado(pictureBox2);
			panel5->Visible = false;
			panel7->Visible = false;



			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~form2()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		System::Windows::Forms::Label^ label4; System::Windows::Forms::Panel^ panel1;
	protected:
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::Button^ AimlegitClick;
	private: System::Windows::Forms::Button^ AimNeck;
	private: System::Windows::Forms::Label^ label3;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ button1;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::PictureBox^ pictureBox4;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::Panel^ panel5;
	private: System::Windows::Forms::Panel^ panel6;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Label^ label9;

	private: System::Windows::Forms::Panel^ panel7;
	private: System::Windows::Forms::Panel^ panel8;
	private: System::Windows::Forms::Button^ button8;

	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Label^ label11;



		   //funções liga e desliga

		   Timer^ particleTimer = gcnew Timer();
		   bool streamModeAtivado = true;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
		   bool precisionAtivado = false;
		   bool aimLegitAtivado = false;
		   bool aimNeckAtivado = false;
	private: System::Windows::Forms::Label^ label1;

		   bool aimBotAtivado = false;




	private: void OcultarDoAltTab() {
		HWND hWnd = static_cast<HWND>(this->Handle.ToPointer());
		LONG exStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
		SetWindowLong(hWnd, GWL_EXSTYLE, exStyle | WS_EX_TOOLWINDOW);
	}







	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
		[System::Runtime::InteropServices::DllImport("user32.dll")]
			static int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);

		[System::Runtime::InteropServices::DllImport("user32.dll")]
			static bool ReleaseCapture();

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(form2::typeid));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->AimNeck = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->AimlegitClick = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->panel7 = (gcnew System::Windows::Forms::Panel());
			this->panel8 = (gcnew System::Windows::Forms::Panel());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel4->SuspendLayout();
			this->panel5->SuspendLayout();
			this->panel6->SuspendLayout();
			this->panel7->SuspendLayout();
			this->panel8->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->pictureBox4);
			this->panel1->Controls->Add(this->pictureBox3);
			this->panel1->Controls->Add(this->pictureBox2);
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Location = System::Drawing::Point(14, 10);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(90, 291);
			this->panel1->TabIndex = 0;
			this->panel1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &form2::form2_MouseDown);
			// 
			// pictureBox4
			// 
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(20, 215);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(40, 40);
			this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox4->TabIndex = 3;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->Click += gcnew System::EventHandler(this, &form2::pictureBox4_Click);
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(20, 160);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(40, 40);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox3->TabIndex = 2;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Click += gcnew System::EventHandler(this, &form2::pictureBox3_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(20, 103);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(40, 40);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &form2::pictureBox2_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(4, 7);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(74, 73);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->panel3);
			this->panel2->Location = System::Drawing::Point(110, 10);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(355, 303);
			this->panel2->TabIndex = 1;
			this->panel2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &form2::form2_MouseDown);
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(16)), static_cast<System::Int32>(static_cast<System::Byte>(16)),
				static_cast<System::Int32>(static_cast<System::Byte>(16)));
			this->panel3->Controls->Add(this->label1);
			this->panel3->Controls->Add(this->label4);
			this->panel3->Controls->Add(this->button1);
			this->panel3->Controls->Add(this->label5);
			this->panel3->Controls->Add(this->AimNeck);
			this->panel3->Controls->Add(this->label3);
			this->panel3->Controls->Add(this->AimlegitClick);
			this->panel3->Controls->Add(this->label2);
			this->panel3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(16)), static_cast<System::Int32>(static_cast<System::Byte>(16)),
				static_cast<System::Int32>(static_cast<System::Byte>(16)));
			this->panel3->Location = System::Drawing::Point(10, 9);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(332, 282);
			this->panel3->TabIndex = 0;
			this->panel3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &form2::form2_MouseDown);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(138, 7);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(31, 15);
			this->label1->TabIndex = 11;
			this->label1->Text = L"合法";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(120, 9);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(58, 12);
			this->label4->TabIndex = 11;
			this->label4->Text = L"エイムボット";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(229, 103);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(23, 23);
			this->button1->TabIndex = 10;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &form2::aimbot_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(23, 106);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(56, 15);
			this->label5->TabIndex = 9;
			this->label5->Text = L"自动瞄准";
			// 
			// AimNeck
			// 
			this->AimNeck->Location = System::Drawing::Point(229, 74);
			this->AimNeck->Name = L"AimNeck";
			this->AimNeck->Size = System::Drawing::Size(23, 23);
			this->AimNeck->TabIndex = 4;
			this->AimNeck->UseVisualStyleBackColor = true;
			this->AimNeck->Click += gcnew System::EventHandler(this, &form2::precision_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(23, 78);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(31, 15);
			this->label3->TabIndex = 3;
			this->label3->Text = L"精准";
			// 
			// AimlegitClick
			// 
			this->AimlegitClick->Location = System::Drawing::Point(229, 45);
			this->AimlegitClick->Name = L"AimlegitClick";
			this->AimlegitClick->Size = System::Drawing::Size(23, 23);
			this->AimlegitClick->TabIndex = 2;
			this->AimlegitClick->UseVisualStyleBackColor = true;
			this->AimlegitClick->Click += gcnew System::EventHandler(this, &form2::AimlegitClick_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(23, 49);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(31, 15);
			this->label2->TabIndex = 1;
			this->label2->Text = L"合法";
			// 
			// panel4
			// 
			this->panel4->Controls->Add(this->panel2);
			this->panel4->Controls->Add(this->panel1);
			this->panel4->Location = System::Drawing::Point(12, 12);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(514, 320);
			this->panel4->TabIndex = 2;
			// 
			// panel5
			// 
			this->panel5->Controls->Add(this->panel6);
			this->panel5->Location = System::Drawing::Point(709, 12);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(335, 270);
			this->panel5->TabIndex = 3;
			// 
			// panel6
			// 
			this->panel6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(16)), static_cast<System::Int32>(static_cast<System::Byte>(16)),
				static_cast<System::Int32>(static_cast<System::Byte>(16)));
			this->panel6->Controls->Add(this->label6);
			this->panel6->Controls->Add(this->button5);
			this->panel6->Controls->Add(this->label8);
			this->panel6->Controls->Add(this->button6);
			this->panel6->Controls->Add(this->label9);
			this->panel6->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(16)), static_cast<System::Int32>(static_cast<System::Byte>(16)),
				static_cast<System::Int32>(static_cast<System::Byte>(16)));
			this->panel6->Location = System::Drawing::Point(17, 24);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(304, 232);
			this->panel6->TabIndex = 0;
			this->panel6->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &form2::form2_MouseDown);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(120, 2);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(50, 24);
			this->label6->TabIndex = 12;
			this->label6->Text = L"\r\nビジュアル";
			this->label6->Click += gcnew System::EventHandler(this, &form2::label6_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(229, 78);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(23, 23);
			this->button5->TabIndex = 4;
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &form2::EspClick);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->ForeColor = System::Drawing::Color::White;
			this->label8->Location = System::Drawing::Point(23, 82);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(58, 15);
			this->label8->TabIndex = 3;
			this->label8->Text = L"额外视觉";
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(229, 49);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(23, 23);
			this->button6->TabIndex = 2;
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &form2::ChamsEnable_Click);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(23, 53);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(58, 15);
			this->label9->TabIndex = 1;
			this->label9->Text = L"轮廓显现";
			// 
			// panel7
			// 
			this->panel7->Controls->Add(this->panel8);
			this->panel7->Location = System::Drawing::Point(709, 409);
			this->panel7->Name = L"panel7";
			this->panel7->Size = System::Drawing::Size(335, 266);
			this->panel7->TabIndex = 4;
			// 
			// panel8
			// 
			this->panel8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(16)), static_cast<System::Int32>(static_cast<System::Byte>(16)),
				static_cast<System::Int32>(static_cast<System::Byte>(16)));
			this->panel8->Controls->Add(this->label7);
			this->panel8->Controls->Add(this->button7);
			this->panel8->Controls->Add(this->label11);
			this->panel8->Controls->Add(this->button8);
			this->panel8->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(16)), static_cast<System::Int32>(static_cast<System::Byte>(16)),
				static_cast<System::Int32>(static_cast<System::Byte>(16)));
			this->panel8->Location = System::Drawing::Point(14, 17);
			this->panel8->Name = L"panel8";
			this->panel8->Size = System::Drawing::Size(307, 233);
			this->panel8->TabIndex = 0;
			this->panel8->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &form2::form2_MouseDown);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::White;
			this->label7->Location = System::Drawing::Point(120, 9);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(36, 12);
			this->label7->TabIndex = 13;
			this->label7->Text = L"その他";
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(229, 110);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(23, 23);
			this->button7->TabIndex = 10;
			this->button7->UseVisualStyleBackColor = true;
			this->button7->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &form2::streamClick);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->ForeColor = System::Drawing::Color::White;
			this->label11->Location = System::Drawing::Point(23, 113);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(55, 15);
			this->label11->TabIndex = 9;
			this->label11->Text = L"幽灵直播";
			// 
			// button8
			// 
			this->button8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->button8->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(105)),
				static_cast<System::Int32>(static_cast<System::Byte>(27)), static_cast<System::Int32>(static_cast<System::Byte>(253)));
			this->button8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button8->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button8->ForeColor = System::Drawing::Color::White;
			this->button8->Location = System::Drawing::Point(47, 158);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(180, 33);
			this->button8->TabIndex = 8;
			this->button8->Text = L"バイパス";
			this->button8->UseVisualStyleBackColor = false;
			this->button8->Click += gcnew System::EventHandler(this, &form2::BYP4SS);
			// 
			// form2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(544, 360);
			this->Controls->Add(this->panel7);
			this->Controls->Add(this->panel5);
			this->Controls->Add(this->panel4);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
			this->Name = L"form2";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Load += gcnew System::EventHandler(this, &form2::form2_Load);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &form2::form2_MouseDown);
			this->panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->panel2->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel5->ResumeLayout(false);
			this->panel6->ResumeLayout(false);
			this->panel6->PerformLayout();
			this->panel7->ResumeLayout(false);
			this->panel8->ResumeLayout(false);
			this->panel8->PerformLayout();
			this->ResumeLayout(false);

		}


#pragma endregion
	private: System::Void form2_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {

			ReleaseCapture();
			SendMessage(this->Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		}

	}
	private: System::Void AimlegitClick_Click(System::Object^ sender, System::EventArgs^ e) {
		aimLegitAtivado = !aimLegitAtivado;
		AimLegit();
		ToggleVisual(AimlegitClick, true);
		ToggleVisual(AimlegitClick, aimLegitAtivado);
	}

	private: System::Void precision_Click(System::Object^ sender, System::EventArgs^ e) {
		precisionAtivado = !precisionAtivado;
		aimNeckAtivado = precisionAtivado;
		if (precisionAtivado) {
			AimPrecision();
		}
		else {
			DisablePrecision();
		}
		ToggleVisual(AimNeck, aimNeckAtivado);
	}

	private: System::Void aimbot_Click(System::Object^ sender, System::EventArgs^ e) {
		aimBotAtivado = !aimBotAtivado;
		AimBot();
		ToggleVisual(button1, true);
		ToggleVisual(button1, aimBotAtivado);
	}

	private: System::Void ChamsEnable_Click(System::Object^ sender, System::EventArgs^ e) {

	}

	private: System::Void EspClick(System::Object^ sender, System::EventArgs^ e) {

	}


	private: System::Void BYP4SS(System::Object^ sender, System::EventArgs^ e) {


		FreeLibraryAndExitThread(g_hModule, 0);  //  DLL se descarrega sozinha
	}


	private: System::Void pictureBox2_Click(System::Object^ sender, System::EventArgs^ e) {
		panel2->Visible = true;
		MarcarSelecionado(pictureBox2);
		panel5->Visible = false;
		panel7->Visible = false;
	}
	private: System::Void pictureBox4_Click(System::Object^ sender, System::EventArgs^ e) {
		panel2->Visible = false;
		panel5->Visible = false;
		panel7->Visible = true;
		MarcarSelecionado(pictureBox4);
	}
	private: System::Void pictureBox3_Click(System::Object^ sender, System::EventArgs^ e) {
		panel2->Visible = false;
		panel5->Visible = true;
		MarcarSelecionado(pictureBox3);
		panel7->Visible = false;
	}

	private: System::Void streamClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		streamModeAtivado = !streamModeAtivado;
		HWND hWnd = static_cast<HWND>(this->Handle.ToPointer());

		if (streamModeAtivado)
		{
			SetWindowDisplayAffinity(hWnd, WDA_EXCLUDEFROMCAPTURE);
			ToggleVisual(button7, true);
		}
		else {
			SetWindowDisplayAffinity(hWnd, WDA_NONE);
			ToggleVisual(button7, false);
		}
	}


	private: System::Void form2_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label6_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label10_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private:
		void AplicarEstiloBotao(Button^ btn) {
			btn->FlatStyle = FlatStyle::Flat;
			btn->FlatAppearance->BorderSize = 0;
			btn->BackColor = Color::FromArgb(30, 30, 30);
			btn->ForeColor = Color::White;
			btn->Font = gcnew Drawing::Font("Segoe UI Semibold", 10.0f, FontStyle::Bold);
			btn->Cursor = Cursors::Hand;

			btn->MouseEnter += gcnew EventHandler(this, &form2::Botao_MouseEnter);
			btn->MouseLeave += gcnew EventHandler(this, &form2::Botao_MouseLeave);
			btn->MouseDown += gcnew MouseEventHandler(this, &form2::Botao_MouseDown);
		}


		void Botao_MouseEnter(Object^ sender, EventArgs^ e) {
			Button^ btn = safe_cast<Button^>(sender);
			if (btn->Text != u8"✔️") {
				btn->BackColor = Color::FromArgb(45, 45, 45);
			}
		}



		void Botao_MouseLeave(Object^ sender, EventArgs^ e) {
			Button^ btn = safe_cast<Button^>(sender);
			if (btn->Text != u8"✔️") {
				btn->BackColor = Color::FromArgb(30, 30, 30);
			}
		}


		void Botao_MouseDown(Object^ sender, MouseEventArgs^ e) {
			Button^ btn = safe_cast<Button^>(sender);
			btn->BackColor = Color::DimGray;
		}



		void ArredondarBotao(Button^ btn) {
			btn->Region = System::Drawing::Region::FromHrgn(CreateRoundRectRgn(0, 0, btn->Width, btn->Height, 10, 10));
		}





		void ToggleVisual(Button^ btn, bool ativado) {
			if (ativado) {
				btn->UseVisualStyleBackColor = false;
				btn->BackColor = Color::FromArgb(105, 27, 253);
				btn->ForeColor = Color::White;
				btn->Text = u8"✔️";
			}
			else {
				btn->UseVisualStyleBackColor = false;
				btn->BackColor = Color::FromArgb(30, 30, 30);
				btn->ForeColor = Color::White;
				btn->Text = L"";
			}
		}


		void MarcarSelecionado(PictureBox^ ativo) {
			List<PictureBox^>^ botoes = gcnew List<PictureBox^>();
			botoes->Add(pictureBox2);
			botoes->Add(pictureBox3);
			botoes->Add(pictureBox4);

			for each (PictureBox ^ pic in botoes) {
				pic->BackColor = Color::FromArgb(16, 16, 16); // padrão dark
			}

			ativo->BackColor = Color::FromArgb(105, 27, 253); // rosa destaque
		}



		void ArredondarPictureBox(PictureBox^ pic) {
			pic->Region = System::Drawing::Region::FromHrgn(CreateRoundRectRgn(0, 0, pic->Width, pic->Height, 10, 10));
		}


		[DllImport("Gdi32.dll")]
		static IntPtr CreateRoundRectRgn(int left, int top, int right, int bottom, int width, int height);


	private: System::Void button8_HoverEnter(System::Object^ sender, System::EventArgs^ e) {
		Button^ btn = safe_cast<Button^>(sender);
		if (btn->Text != u8"✔️")
			btn->BackColor = System::Drawing::Color::FromArgb(105, 27, 253);
	}

	private: System::Void button8_HoverLeave(System::Object^ sender, System::EventArgs^ e) {
		Button^ btn = safe_cast<Button^>(sender);
		if (btn->Text != u8"✔️")
			btn->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
	}

	};
}
