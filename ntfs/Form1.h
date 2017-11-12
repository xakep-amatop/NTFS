#pragma once

namespace ntfs {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::GroupBox^  grInfo;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::ListBox^  lTree;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  lVolume4;

	private: System::Windows::Forms::Label^  lVolume3;

	private: System::Windows::Forms::Label^  lVolume2;

	private: System::Windows::Forms::Label^  lVolume1;
	private: System::Windows::Forms::Label^  lVolume11;

	private: System::Windows::Forms::Label^  lVolume10;

	private: System::Windows::Forms::Label^  lVolume9;

	private: System::Windows::Forms::Label^  lVolume8;

	private: System::Windows::Forms::Label^  lVolume7;

	private: System::Windows::Forms::Label^  lVolume5;
	private: System::Windows::Forms::Label^  lVolume6;










	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->grInfo = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->lTree = (gcnew System::Windows::Forms::ListBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->lVolume1 = (gcnew System::Windows::Forms::Label());
			this->lVolume2 = (gcnew System::Windows::Forms::Label());
			this->lVolume3 = (gcnew System::Windows::Forms::Label());
			this->lVolume4 = (gcnew System::Windows::Forms::Label());
			this->lVolume6 = (gcnew System::Windows::Forms::Label());
			this->lVolume5 = (gcnew System::Windows::Forms::Label());
			this->lVolume7 = (gcnew System::Windows::Forms::Label());
			this->lVolume8 = (gcnew System::Windows::Forms::Label());
			this->lVolume9 = (gcnew System::Windows::Forms::Label());
			this->lVolume10 = (gcnew System::Windows::Forms::Label());
			this->lVolume11 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->grInfo->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 3);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(90, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Локальний диск";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 184);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(579, 377);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// grInfo
			// 
			this->grInfo->Controls->Add(this->lVolume11);
			this->grInfo->Controls->Add(this->lVolume10);
			this->grInfo->Controls->Add(this->lVolume9);
			this->grInfo->Controls->Add(this->lVolume8);
			this->grInfo->Controls->Add(this->lVolume7);
			this->grInfo->Controls->Add(this->lVolume5);
			this->grInfo->Controls->Add(this->lVolume6);
			this->grInfo->Controls->Add(this->lVolume4);
			this->grInfo->Controls->Add(this->lVolume3);
			this->grInfo->Controls->Add(this->lVolume2);
			this->grInfo->Controls->Add(this->lVolume1);
			this->grInfo->Controls->Add(this->label12);
			this->grInfo->Controls->Add(this->label11);
			this->grInfo->Controls->Add(this->label10);
			this->grInfo->Controls->Add(this->label9);
			this->grInfo->Controls->Add(this->label8);
			this->grInfo->Controls->Add(this->label7);
			this->grInfo->Controls->Add(this->label6);
			this->grInfo->Controls->Add(this->label4);
			this->grInfo->Controls->Add(this->label5);
			this->grInfo->Controls->Add(this->label3);
			this->grInfo->Controls->Add(this->label2);
			this->grInfo->Location = System::Drawing::Point(192, 13);
			this->grInfo->Name = L"grInfo";
			this->grInfo->Size = System::Drawing::Size(588, 165);
			this->grInfo->TabIndex = 2;
			this->grInfo->TabStop = false;
			this->grInfo->Text = L"Information";
			this->grInfo->Enter += gcnew System::EventHandler(this, &Form1::groupBox1_Enter);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(16, 19);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(170, 21);
			this->comboBox1->TabIndex = 3;
			// 
			// lTree
			// 
			this->lTree->FormattingEnabled = true;
			this->lTree->Location = System::Drawing::Point(608, 189);
			this->lTree->Name = L"lTree";
			this->lTree->Size = System::Drawing::Size(172, 368);
			this->lTree->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(6, 16);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(63, 15);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Signature:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(6, 91);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(96, 15);
			this->label3->TabIndex = 1;
			this->label3->Text = L"Bytes per sector:";
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(6, 41);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(111, 15);
			this->label5->TabIndex = 3;
			this->label5->Text = L"Sectors per cluster:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(210, 66);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(156, 15);
			this->label4->TabIndex = 4;
			this->label4->Text = L"Logical start cluster of MFT:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(6, 66);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(126, 15);
			this->label6->TabIndex = 5;
			this->label6->Text = L"Bytes per MFT record:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(210, 116);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(131, 15);
			this->label7->TabIndex = 6;
			this->label7->Text = L"Volume serial number:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(210, 91);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(139, 15);
			this->label8->TabIndex = 7;
			this->label8->Text = L"Total sectors on volume:";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(6, 141);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(107, 15);
			this->label9->TabIndex = 8;
			this->label9->Text = L"Size of free space:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(6, 116);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(90, 15);
			this->label10->TabIndex = 9;
			this->label10->Text = L"Size of volume:";
			this->label10->Click += gcnew System::EventHandler(this, &Form1::label10_Click);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(210, 16);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(102, 15);
			this->label11->TabIndex = 10;
			this->label11->Text = L"Media descriptor:";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label12->Location = System::Drawing::Point(210, 41);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(188, 15);
			this->label12->TabIndex = 11;
			this->label12->Text = L"Mirror logical start cluster of MFT:";
			// 
			// lVolume1
			// 
			this->lVolume1->AutoSize = true;
			this->lVolume1->Location = System::Drawing::Point(130, 18);
			this->lVolume1->Name = L"lVolume1";
			this->lVolume1->Size = System::Drawing::Size(0, 13);
			this->lVolume1->TabIndex = 12;
			// 
			// lVolume2
			// 
			this->lVolume2->AutoSize = true;
			this->lVolume2->Location = System::Drawing::Point(130, 43);
			this->lVolume2->Name = L"lVolume2";
			this->lVolume2->Size = System::Drawing::Size(0, 13);
			this->lVolume2->TabIndex = 13;
			this->lVolume2->Click += gcnew System::EventHandler(this, &Form1::label14_Click);
			// 
			// lVolume3
			// 
			this->lVolume3->AutoSize = true;
			this->lVolume3->Location = System::Drawing::Point(130, 68);
			this->lVolume3->Name = L"lVolume3";
			this->lVolume3->Size = System::Drawing::Size(0, 13);
			this->lVolume3->TabIndex = 14;
			// 
			// lVolume4
			// 
			this->lVolume4->AutoSize = true;
			this->lVolume4->Location = System::Drawing::Point(130, 93);
			this->lVolume4->Name = L"lVolume4";
			this->lVolume4->Size = System::Drawing::Size(0, 13);
			this->lVolume4->TabIndex = 15;
			// 
			// lVolume6
			// 
			this->lVolume6->AutoSize = true;
			this->lVolume6->Location = System::Drawing::Point(130, 143);
			this->lVolume6->Name = L"lVolume6";
			this->lVolume6->Size = System::Drawing::Size(0, 13);
			this->lVolume6->TabIndex = 16;
			// 
			// lVolume5
			// 
			this->lVolume5->AutoSize = true;
			this->lVolume5->Location = System::Drawing::Point(130, 118);
			this->lVolume5->Name = L"lVolume5";
			this->lVolume5->Size = System::Drawing::Size(0, 13);
			this->lVolume5->TabIndex = 17;
			// 
			// lVolume7
			// 
			this->lVolume7->AutoSize = true;
			this->lVolume7->Location = System::Drawing::Point(402, 18);
			this->lVolume7->Name = L"lVolume7";
			this->lVolume7->Size = System::Drawing::Size(0, 13);
			this->lVolume7->TabIndex = 18;
			// 
			// lVolume8
			// 
			this->lVolume8->AutoSize = true;
			this->lVolume8->Location = System::Drawing::Point(402, 43);
			this->lVolume8->Name = L"lVolume8";
			this->lVolume8->Size = System::Drawing::Size(0, 13);
			this->lVolume8->TabIndex = 19;
			// 
			// lVolume9
			// 
			this->lVolume9->AutoSize = true;
			this->lVolume9->Location = System::Drawing::Point(402, 68);
			this->lVolume9->Name = L"lVolume9";
			this->lVolume9->Size = System::Drawing::Size(0, 13);
			this->lVolume9->TabIndex = 20;
			// 
			// lVolume10
			// 
			this->lVolume10->AutoSize = true;
			this->lVolume10->Location = System::Drawing::Point(402, 93);
			this->lVolume10->Name = L"lVolume10";
			this->lVolume10->Size = System::Drawing::Size(0, 13);
			this->lVolume10->TabIndex = 21;
			// 
			// lVolume11
			// 
			this->lVolume11->AutoSize = true;
			this->lVolume11->Location = System::Drawing::Point(402, 118);
			this->lVolume11->Name = L"lVolume11";
			this->lVolume11->Size = System::Drawing::Size(0, 13);
			this->lVolume11->TabIndex = 22;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(792, 566);
			this->Controls->Add(this->lTree);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->grInfo);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(800, 600);
			this->MinimumSize = System::Drawing::Size(800, 600);
			this->Name = L"Form1";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Disk";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->grInfo->ResumeLayout(false);
			this->grInfo->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void label10_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label14_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

