#pragma once
#include <windows.h>
#include <windowsx.h>
#include "form2.h"
#include "Globals.h"

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
	using namespace System::Management;
	using namespace System::Collections::Generic;




	/// <summary>
	/// Summary for form1
	/// </summary>
	public ref class form1 : public System::Windows::Forms::Form
	{

	public:
		form1(void)
		{

			InitializeComponent();
			this->TopMost = true;
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &form1::form1_MouseDown);
			bool isStreamModeEnabled = true; // já ativado

			this->DoubleBuffered = true; // suaviza flicker

			this->loginbutton->Region = System::Drawing::Region::FromHrgn(
				CreateRoundRectRgn(0, 0, loginbutton->Width, loginbutton->Height, 10, 10)
			);

			this->discordid->Region = System::Drawing::Region::FromHrgn(
				CreateRoundRectRgn(0, 0, this->discordid->Width, this->discordid->Height, 10, 10)
			);

			if (isStreamModeEnabled) {
				HWND hWnd = static_cast<HWND>(this->Handle.ToPointer());
				SetWindowDisplayAffinity(hWnd, WDA_EXCLUDEFROMCAPTURE);
				this->ShowInTaskbar = false;
				this->TopMost = true;
				OcultarDoAltTab();
			}


			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~form1()
		{

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ loginbutton;
	protected:

	private: System::Windows::Forms::TextBox^ discordid;
	private: System::Windows::Forms::PictureBox^ pictureBox1;

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
		[DllImport("Gdi32.dll")]
		static IntPtr CreateRoundRectRgn(int left, int top, int right, int bottom, int width, int height);


		ref struct Particle {
			float x, y, speedX, speedY, size;
			Color color;
		};

		List<Particle^>^ particles = gcnew List<Particle^>();
		Random^ random = gcnew Random();
		Timer^ particleTimer = gcnew Timer();


	private: void OcultarDoAltTab() {
		HWND hWnd = static_cast<HWND>(this->Handle.ToPointer());
		LONG exStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
		SetWindowLong(hWnd, GWL_EXSTYLE, exStyle | WS_EX_TOOLWINDOW);
	}
	private: void CreateParticles(int count) {
		for (int i = 0; i < count; i++) {
			Particle^ p = gcnew Particle();
			p->x = random->Next(0, this->Width);
			p->y = random->Next(0, this->Height);
			p->speedX = (float)(random->NextDouble() * 2 - 1);
			p->speedY = (float)(random->NextDouble() * 2 - 1);
			p->size = random->Next(2, 6);
			p->color = Color::White;
			particles->Add(p);
		}
	}
	private: void UpdateParticles(System::Object^ sender, System::EventArgs^ e) {
		for each (Particle ^ p in particles) {
			p->x += p->speedX;
			p->y += p->speedY;

			if (p->x < 0 || p->x > this->Width) p->speedX *= -1;
			if (p->y < 0 || p->y > this->Height) p->speedY *= -1;
		}

		this->Invalidate(); // força repintura
	}
	private: void DrawParticles(System::Object^ sender, PaintEventArgs^ e) {
		Graphics^ g = e->Graphics;

		for each (Particle ^ p in particles) {
			SolidBrush^ brush = gcnew SolidBrush(p->color);
			g->FillEllipse(brush, p->x, p->y, p->size, p->size);
			delete brush;

		}
	}



#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(form1::typeid));
			   this->loginbutton = (gcnew System::Windows::Forms::Button());
			   this->discordid = (gcnew System::Windows::Forms::TextBox());
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // loginbutton
			   // 
			   this->loginbutton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				   static_cast<System::Int32>(static_cast<System::Byte>(30)));
			   this->loginbutton->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->loginbutton->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)),
				   static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)));
			   this->loginbutton->FlatAppearance->BorderSize = 0;
			   this->loginbutton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(105)),
				   static_cast<System::Int32>(static_cast<System::Byte>(27)), static_cast<System::Int32>(static_cast<System::Byte>(253)));
			   this->loginbutton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->loginbutton->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10, System::Drawing::FontStyle::Bold));
			   this->loginbutton->ForeColor = System::Drawing::Color::White;
			   this->loginbutton->Location = System::Drawing::Point(174, 236);
			   this->loginbutton->Name = L"loginbutton";
			   this->loginbutton->Size = System::Drawing::Size(180, 33);
			   this->loginbutton->TabIndex = 7;
			   this->loginbutton->TabStop = false;
			   this->loginbutton->Text = L"Continue";
			   this->loginbutton->UseVisualStyleBackColor = false;
			   this->loginbutton->Click += gcnew System::EventHandler(this, &form1::button1_Click);
			   this->loginbutton->MouseEnter += gcnew System::EventHandler(this, &form1::loginbutton_HoverEnter);
			   this->loginbutton->MouseLeave += gcnew System::EventHandler(this, &form1::loginbutton_HoverLeave);
			   // 
			   // discordid
			   // 
			   this->discordid->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->discordid->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(20)),
				   static_cast<System::Int32>(static_cast<System::Byte>(20)));
			   this->discordid->BorderStyle = System::Windows::Forms::BorderStyle::None;
			   this->discordid->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			   this->discordid->ForeColor = System::Drawing::Color::White;
			   this->discordid->Location = System::Drawing::Point(188, 211);
			   this->discordid->Margin = System::Windows::Forms::Padding(4);
			   this->discordid->Name = L"discordid";
			   this->discordid->Size = System::Drawing::Size(153, 18);
			   this->discordid->TabIndex = 6;
			   this->discordid->Text = L"Enter Discord ID";
			   this->discordid->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			   this->discordid->TextChanged += gcnew System::EventHandler(this, &form1::textBox1_TextChanged);
			   this->discordid->GotFocus += gcnew System::EventHandler(this, &form1::discordid_GotFocus);
			   this->discordid->LostFocus += gcnew System::EventHandler(this, &form1::discordid_LostFocus);
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			   this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			   this->pictureBox1->Location = System::Drawing::Point(199, 92);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(130, 112);
			   this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			   this->pictureBox1->TabIndex = 8;
			   this->pictureBox1->TabStop = false;
			   this->pictureBox1->Click += gcnew System::EventHandler(this, &form1::pictureBox1_Click_1);
			   // 
			   // form1
			   // 
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			   this->BackColor = System::Drawing::Color::Black;
			   this->ClientSize = System::Drawing::Size(544, 360);
			   this->Controls->Add(this->pictureBox1);
			   this->Controls->Add(this->discordid);
			   this->Controls->Add(this->loginbutton);
			   this->ForeColor = System::Drawing::Color::Black;
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			   this->Name = L"form1";
			   this->ShowIcon = false;
			   this->ShowInTaskbar = false;
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"form1";
			   this->TopMost = true;
			   this->Load += gcnew System::EventHandler(this, &form1::form1_Load);
			   this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &form1::form1_MouseDown);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {

	}
	private: String^ GetMachineUUID() {
		try {
			ManagementObjectSearcher^ searcher = gcnew ManagementObjectSearcher("SELECT UUID FROM Win32_ComputerSystemProduct");

			for each (ManagementObject ^ obj in searcher->Get()) {
				return obj["UUID"]->ToString();
			}
			return "UUID_NAO_ENCONTRADO";
		}
		catch (Exception^ ex) {
			return "ERRO: " + ex->Message;
		}
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ idDigitado = discordid->Text->Trim(); // pega o texto do input
		String^ uuidAtual = GetMachineUUID();

		// Simulando listas autorizadas
		array<String^>^ idsAutorizados = gcnew array<String^> {
			"1271880342667788461",//susu
				"934474331474501682",//mv
				"528390995520520202",//dudu
				"1249935666134126636",//pedrin
				"834537776124264459",//pedrin


		};

		array<String^>^ uuidsAutorizados = gcnew array<String^> {
			"03FF0210-04E0-0508-B906-510700080009",//susu
				"03D502E0-045E-0565-6506-C20700080009",//mv
				"0FEF26BB-AE8E-A464-48F4-107C61A57F5F",//dudu
				"B6D96A36-6006-9716-A6D8-D843AE93C914",//pedrin
				"4B59A1A8-C9C5-0000-0000-000000000000",//gattiz


		};

		// Verificação dupla
		if (Array::IndexOf(idsAutorizados, idDigitado) >= 0 &&
			Array::IndexOf(uuidsAutorizados, uuidAtual) >= 0)
		{
			//  Libera acesso
			form2^ janela2 = gcnew form2();
			janela2->Show();
			this->Hide();
		}
		else {
			this->Close(); //  Fecha o app imediatamente

		}

	}


	private: System::Void form1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			ReleaseCapture();
			SendMessage(this->Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		}


	}

	private: System::Void discordid_GotFocus(System::Object^ sender, System::EventArgs^ e) {
		if (discordid->Text == L"Enter Discord ID") {
			discordid->Text = L"";
		}
	}

	private: System::Void discordid_LostFocus(System::Object^ sender, System::EventArgs^ e) {
		if (discordid->Text == L"") {
			discordid->Text = L"Enter Discord ID";
		}
	}

	private: System::Void form1_Load(System::Object^ sender, System::EventArgs^ e) {

		this->discordid->Region = System::Drawing::Region::FromHrgn(
			CreateRoundRectRgn(0, 0, this->discordid->Width + 1, this->discordid->Height + 1, 10, 10)
		);
	}


	public:
		static void RunPainel() {
			// Cria uma thread nova STA que roda o painel
			form1^ painel = gcnew form1();
			System::Threading::Thread^ t = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(painel, &form1::ExecutarSTA));
			t->SetApartmentState(System::Threading::ApartmentState::STA);
			t->Start();
		}

		// Método de instância que roda o loop da UI
		void ExecutarSTA() {
			Application::EnableVisualStyles();
			Application::SetCompatibleTextRenderingDefault(false);
			Application::Run(this);
		}


	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}

		   System::Void loginbutton_HoverEnter(System::Object^ sender, System::EventArgs^ e) {
			   Button^ btn = safe_cast<Button^>(sender);
			   btn->BackColor = System::Drawing::Color::FromArgb(105, 27, 253);
		   }

		   System::Void loginbutton_HoverLeave(System::Object^ sender, System::EventArgs^ e) {
			   Button^ btn = safe_cast<Button^>(sender);
			   btn->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
		   }
	};
}