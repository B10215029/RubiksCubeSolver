#pragma once
#include <Windows.h>
#include "RubiksCube.h"

namespace RubiksCubeSolver {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// RubiksCubeSimulator 的摘要
	/// </summary>
	public ref class RubiksCubeSimulator : public System::Windows::Forms::Form
	{
	public:
		RubiksCubeSimulator(void)
		{
			InitializeComponent();
			this->undoTimer = (gcnew System::Windows::Forms::Timer());
			this->redoTimer = (gcnew System::Windows::Forms::Timer());
			this->undoTimer->Tick += (gcnew System::EventHandler(this, &RubiksCubeSimulator::undoTimer_Tick));
			this->redoTimer->Tick += (gcnew System::EventHandler(this, &RubiksCubeSimulator::redoTimer_Tick));
			this->panel1->MouseWheel += (gcnew System::Windows::Forms::MouseEventHandler(this, &RubiksCubeSimulator::panel1_MouseWheel));
			mouseDown = false;
			zoom = 0;
			cubeTextureID = UINT_MAX;
			cube = new RubiksCube(3);
			hDC = GetDC((HWND)(panel1->Handle.ToInt32()));
			hGLRC = initializeOpenGLContext(hDC);
			this->initTexture();
		}
		HGLRC initializeOpenGLContext(HDC hDC);
		void initProgram();
		void initTexture();
		void resize();
		void mouseMove(int x, int y);
		void draw();

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~RubiksCubeSimulator()
		{
			if (components)
			{
				delete components;
				if (cube) {
					delete cube;
				}
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		HDC hDC;
		HGLRC hGLRC;
		RubiksCube* cube;
		unsigned int programID;
		unsigned int matrixLocationID;
		unsigned int projectionMatrixLocationID;
		unsigned int textureLocationID;
		unsigned int sizeLocationID;
		unsigned int cubeTextureID;
		unsigned int vertexArrayID;
		float *modelMatrixPtr;
		float *viewMatrixPtr;
		float *projectionMatrixPtr;
		int previousMousePositionX;
		int previousMousePositionY;
		float zoom;
		bool mouseDown;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
	private: System::Windows::Forms::Button^  rotateButton;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  typeTextBox;
	private: System::Windows::Forms::TextBox^  columnTextBox;
	private: System::Windows::Forms::TextBox^  angleTextBox;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel4;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  textBoxF;
	private: System::Windows::Forms::TextBox^  textBoxR;
	private: System::Windows::Forms::TextBox^  textBoxU;
	private: System::Windows::Forms::TextBox^  textBoxB;
	private: System::Windows::Forms::TextBox^  textBoxL;
	private: System::Windows::Forms::TextBox^  textBoxD;
	private: System::Windows::Forms::Button^  rotateFButton;
	private: System::Windows::Forms::Button^  reverseFButton;
	private: System::Windows::Forms::Button^  rotateRButton;
	private: System::Windows::Forms::Button^  rotateUButton;
	private: System::Windows::Forms::Button^  rotateBButton;
	private: System::Windows::Forms::Button^  rotateLButton;
	private: System::Windows::Forms::Button^  rotateDButton;
	private: System::Windows::Forms::Button^  reverseRButton;
	private: System::Windows::Forms::Button^  reverseUButton;
	private: System::Windows::Forms::Button^  reverseBButton;
	private: System::Windows::Forms::Button^  reverseLButton;
	private: System::Windows::Forms::Button^  reverseDButton;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel6;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel7;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TextBox^  sizeTextBox;
	private: System::Windows::Forms::Button^  resetButton;
	private: System::Windows::Forms::Button^  shufflrButton;
	private: System::Windows::Forms::Button^  solveButton;
	private: System::Windows::Forms::Label^  labelHtm;
	private: System::Windows::Forms::Label^  labelQtm;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel8;
	private: System::Windows::Forms::Button^  undoButton;
	private: System::Windows::Forms::Button^  redoButton;
	private: System::Windows::Forms::Timer^  redoTimer;
	private: System::Windows::Forms::Timer^  undoTimer;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel9;
private: System::Windows::Forms::TextBox^  textBox1;



			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->rotateButton = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->typeTextBox = (gcnew System::Windows::Forms::TextBox());
			this->columnTextBox = (gcnew System::Windows::Forms::TextBox());
			this->angleTextBox = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBoxF = (gcnew System::Windows::Forms::TextBox());
			this->textBoxR = (gcnew System::Windows::Forms::TextBox());
			this->textBoxU = (gcnew System::Windows::Forms::TextBox());
			this->textBoxB = (gcnew System::Windows::Forms::TextBox());
			this->textBoxL = (gcnew System::Windows::Forms::TextBox());
			this->textBoxD = (gcnew System::Windows::Forms::TextBox());
			this->rotateFButton = (gcnew System::Windows::Forms::Button());
			this->reverseFButton = (gcnew System::Windows::Forms::Button());
			this->rotateRButton = (gcnew System::Windows::Forms::Button());
			this->rotateUButton = (gcnew System::Windows::Forms::Button());
			this->rotateBButton = (gcnew System::Windows::Forms::Button());
			this->rotateLButton = (gcnew System::Windows::Forms::Button());
			this->rotateDButton = (gcnew System::Windows::Forms::Button());
			this->reverseRButton = (gcnew System::Windows::Forms::Button());
			this->reverseUButton = (gcnew System::Windows::Forms::Button());
			this->reverseBButton = (gcnew System::Windows::Forms::Button());
			this->reverseLButton = (gcnew System::Windows::Forms::Button());
			this->reverseDButton = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel7 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->sizeTextBox = (gcnew System::Windows::Forms::TextBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->resetButton = (gcnew System::Windows::Forms::Button());
			this->shufflrButton = (gcnew System::Windows::Forms::Button());
			this->solveButton = (gcnew System::Windows::Forms::Button());
			this->labelHtm = (gcnew System::Windows::Forms::Label());
			this->labelQtm = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel8 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->undoButton = (gcnew System::Windows::Forms::Button());
			this->redoButton = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel9 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel5->SuspendLayout();
			this->tableLayoutPanel6->SuspendLayout();
			this->tableLayoutPanel7->SuspendLayout();
			this->tableLayoutPanel8->SuspendLayout();
			this->tableLayoutPanel9->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(3, 3);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(778, 564);
			this->panel1->TabIndex = 0;
			this->panel1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &RubiksCubeSimulator::panel1_MouseDown);
			this->panel1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &RubiksCubeSimulator::panel1_MouseMove);
			this->panel1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &RubiksCubeSimulator::panel1_MouseUp);
			this->panel1->Resize += gcnew System::EventHandler(this, &RubiksCubeSimulator::panel1_Resize);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel4, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->panel1, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 75)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(784, 761);
			this->tableLayoutPanel1->TabIndex = 1;
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 3;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				60)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				20)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				20)));
			this->tableLayoutPanel4->Controls->Add(this->tableLayoutPanel2, 1, 0);
			this->tableLayoutPanel4->Controls->Add(this->tableLayoutPanel5, 0, 0);
			this->tableLayoutPanel4->Controls->Add(this->tableLayoutPanel6, 2, 0);
			this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel4->Location = System::Drawing::Point(3, 573);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 1;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(778, 185);
			this->tableLayoutPanel4->TabIndex = 0;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 1;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel2->Controls->Add(this->rotateButton, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->tableLayoutPanel3, 0, 0);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(469, 3);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 75)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(149, 179);
			this->tableLayoutPanel2->TabIndex = 1;
			// 
			// rotateButton
			// 
			this->rotateButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rotateButton->Location = System::Drawing::Point(3, 137);
			this->rotateButton->Name = L"rotateButton";
			this->rotateButton->Size = System::Drawing::Size(143, 39);
			this->rotateButton->TabIndex = 0;
			this->rotateButton->Text = L"Rotate";
			this->rotateButton->UseVisualStyleBackColor = true;
			this->rotateButton->Click += gcnew System::EventHandler(this, &RubiksCubeSimulator::rotateButton_Click);
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 2;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel3->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->label2, 0, 1);
			this->tableLayoutPanel3->Controls->Add(this->label3, 0, 2);
			this->tableLayoutPanel3->Controls->Add(this->typeTextBox, 1, 0);
			this->tableLayoutPanel3->Controls->Add(this->columnTextBox, 1, 1);
			this->tableLayoutPanel3->Controls->Add(this->angleTextBox, 1, 2);
			this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel3->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 3;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(143, 128);
			this->tableLayoutPanel3->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label1->Location = System::Drawing::Point(3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(65, 42);
			this->label1->TabIndex = 0;
			this->label1->Text = L"type";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label2->Location = System::Drawing::Point(3, 42);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(65, 42);
			this->label2->TabIndex = 1;
			this->label2->Text = L"column";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label3->Location = System::Drawing::Point(3, 84);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(65, 44);
			this->label3->TabIndex = 2;
			this->label3->Text = L"angle";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// typeTextBox
			// 
			this->typeTextBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->typeTextBox->Location = System::Drawing::Point(74, 3);
			this->typeTextBox->Name = L"typeTextBox";
			this->typeTextBox->Size = System::Drawing::Size(66, 22);
			this->typeTextBox->TabIndex = 3;
			this->typeTextBox->Text = L"0";
			// 
			// columnTextBox
			// 
			this->columnTextBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->columnTextBox->Location = System::Drawing::Point(74, 45);
			this->columnTextBox->Name = L"columnTextBox";
			this->columnTextBox->Size = System::Drawing::Size(66, 22);
			this->columnTextBox->TabIndex = 4;
			this->columnTextBox->Text = L"1";
			// 
			// angleTextBox
			// 
			this->angleTextBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->angleTextBox->Location = System::Drawing::Point(74, 87);
			this->angleTextBox->Name = L"angleTextBox";
			this->angleTextBox->Size = System::Drawing::Size(66, 22);
			this->angleTextBox->TabIndex = 5;
			this->angleTextBox->Text = L"1";
			// 
			// tableLayoutPanel5
			// 
			this->tableLayoutPanel5->ColumnCount = 6;
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				16.66667F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				16.66667F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				16.66667F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				16.66667F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				16.66667F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				16.66667F)));
			this->tableLayoutPanel5->Controls->Add(this->label4, 0, 0);
			this->tableLayoutPanel5->Controls->Add(this->label5, 1, 0);
			this->tableLayoutPanel5->Controls->Add(this->label6, 2, 0);
			this->tableLayoutPanel5->Controls->Add(this->label7, 3, 0);
			this->tableLayoutPanel5->Controls->Add(this->label8, 4, 0);
			this->tableLayoutPanel5->Controls->Add(this->label9, 5, 0);
			this->tableLayoutPanel5->Controls->Add(this->textBoxF, 0, 1);
			this->tableLayoutPanel5->Controls->Add(this->textBoxR, 1, 1);
			this->tableLayoutPanel5->Controls->Add(this->textBoxU, 2, 1);
			this->tableLayoutPanel5->Controls->Add(this->textBoxB, 3, 1);
			this->tableLayoutPanel5->Controls->Add(this->textBoxL, 4, 1);
			this->tableLayoutPanel5->Controls->Add(this->textBoxD, 5, 1);
			this->tableLayoutPanel5->Controls->Add(this->rotateFButton, 0, 2);
			this->tableLayoutPanel5->Controls->Add(this->reverseFButton, 0, 3);
			this->tableLayoutPanel5->Controls->Add(this->rotateRButton, 1, 2);
			this->tableLayoutPanel5->Controls->Add(this->rotateUButton, 2, 2);
			this->tableLayoutPanel5->Controls->Add(this->rotateBButton, 3, 2);
			this->tableLayoutPanel5->Controls->Add(this->rotateLButton, 4, 2);
			this->tableLayoutPanel5->Controls->Add(this->rotateDButton, 5, 2);
			this->tableLayoutPanel5->Controls->Add(this->reverseRButton, 1, 3);
			this->tableLayoutPanel5->Controls->Add(this->reverseUButton, 2, 3);
			this->tableLayoutPanel5->Controls->Add(this->reverseBButton, 3, 3);
			this->tableLayoutPanel5->Controls->Add(this->reverseLButton, 4, 3);
			this->tableLayoutPanel5->Controls->Add(this->reverseDButton, 5, 3);
			this->tableLayoutPanel5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel5->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
			this->tableLayoutPanel5->RowCount = 4;
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel5->Size = System::Drawing::Size(460, 179);
			this->tableLayoutPanel5->TabIndex = 2;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label4->Location = System::Drawing::Point(3, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(70, 44);
			this->label4->TabIndex = 0;
			this->label4->Text = L"F(綠)";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label5->Location = System::Drawing::Point(79, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(70, 44);
			this->label5->TabIndex = 1;
			this->label5->Text = L"R(紅)";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label6->Location = System::Drawing::Point(155, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(70, 44);
			this->label6->TabIndex = 2;
			this->label6->Text = L"U(白)";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label7->Location = System::Drawing::Point(231, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(70, 44);
			this->label7->TabIndex = 3;
			this->label7->Text = L"B(藍)";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label8->Location = System::Drawing::Point(307, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(70, 44);
			this->label8->TabIndex = 4;
			this->label8->Text = L"L(橘)";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label9->Location = System::Drawing::Point(383, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(74, 44);
			this->label9->TabIndex = 5;
			this->label9->Text = L"D(黃)";
			this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// textBoxF
			// 
			this->textBoxF->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBoxF->Location = System::Drawing::Point(3, 47);
			this->textBoxF->Name = L"textBoxF";
			this->textBoxF->Size = System::Drawing::Size(70, 22);
			this->textBoxF->TabIndex = 6;
			this->textBoxF->Text = L"1";
			// 
			// textBoxR
			// 
			this->textBoxR->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBoxR->Location = System::Drawing::Point(79, 47);
			this->textBoxR->Name = L"textBoxR";
			this->textBoxR->Size = System::Drawing::Size(70, 22);
			this->textBoxR->TabIndex = 6;
			this->textBoxR->Text = L"1";
			// 
			// textBoxU
			// 
			this->textBoxU->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBoxU->Location = System::Drawing::Point(155, 47);
			this->textBoxU->Name = L"textBoxU";
			this->textBoxU->Size = System::Drawing::Size(70, 22);
			this->textBoxU->TabIndex = 6;
			this->textBoxU->Text = L"1";
			// 
			// textBoxB
			// 
			this->textBoxB->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBoxB->Location = System::Drawing::Point(231, 47);
			this->textBoxB->Name = L"textBoxB";
			this->textBoxB->Size = System::Drawing::Size(70, 22);
			this->textBoxB->TabIndex = 6;
			this->textBoxB->Text = L"1";
			// 
			// textBoxL
			// 
			this->textBoxL->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBoxL->Location = System::Drawing::Point(307, 47);
			this->textBoxL->Name = L"textBoxL";
			this->textBoxL->Size = System::Drawing::Size(70, 22);
			this->textBoxL->TabIndex = 6;
			this->textBoxL->Text = L"1";
			// 
			// textBoxD
			// 
			this->textBoxD->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBoxD->Location = System::Drawing::Point(383, 47);
			this->textBoxD->Name = L"textBoxD";
			this->textBoxD->Size = System::Drawing::Size(74, 22);
			this->textBoxD->TabIndex = 6;
			this->textBoxD->Text = L"1";
			// 
			// rotateFButton
			// 
			this->rotateFButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rotateFButton->Location = System::Drawing::Point(3, 91);
			this->rotateFButton->Name = L"rotateFButton";
			this->rotateFButton->Size = System::Drawing::Size(70, 38);
			this->rotateFButton->TabIndex = 7;
			this->rotateFButton->Text = L"Rotate";
			this->rotateFButton->UseVisualStyleBackColor = true;
			this->rotateFButton->Click += gcnew System::EventHandler(this, &RubiksCubeSimulator::rotateFButton_Click);
			// 
			// reverseFButton
			// 
			this->reverseFButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->reverseFButton->Location = System::Drawing::Point(3, 135);
			this->reverseFButton->Name = L"reverseFButton";
			this->reverseFButton->Size = System::Drawing::Size(70, 41);
			this->reverseFButton->TabIndex = 7;
			this->reverseFButton->Text = L"Reverse";
			this->reverseFButton->UseVisualStyleBackColor = true;
			this->reverseFButton->Click += gcnew System::EventHandler(this, &RubiksCubeSimulator::reverseFButton_Click);
			// 
			// rotateRButton
			// 
			this->rotateRButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rotateRButton->Location = System::Drawing::Point(79, 91);
			this->rotateRButton->Name = L"rotateRButton";
			this->rotateRButton->Size = System::Drawing::Size(70, 38);
			this->rotateRButton->TabIndex = 7;
			this->rotateRButton->Text = L"Rotate";
			this->rotateRButton->UseVisualStyleBackColor = true;
			this->rotateRButton->Click += gcnew System::EventHandler(this, &RubiksCubeSimulator::rotateRButton_Click);
			// 
			// rotateUButton
			// 
			this->rotateUButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rotateUButton->Location = System::Drawing::Point(155, 91);
			this->rotateUButton->Name = L"rotateUButton";
			this->rotateUButton->Size = System::Drawing::Size(70, 38);
			this->rotateUButton->TabIndex = 7;
			this->rotateUButton->Text = L"Rotate";
			this->rotateUButton->UseVisualStyleBackColor = true;
			this->rotateUButton->Click += gcnew System::EventHandler(this, &RubiksCubeSimulator::rotateUButton_Click);
			// 
			// rotateBButton
			// 
			this->rotateBButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rotateBButton->Location = System::Drawing::Point(231, 91);
			this->rotateBButton->Name = L"rotateBButton";
			this->rotateBButton->Size = System::Drawing::Size(70, 38);
			this->rotateBButton->TabIndex = 7;
			this->rotateBButton->Text = L"Rotate";
			this->rotateBButton->UseVisualStyleBackColor = true;
			this->rotateBButton->Click += gcnew System::EventHandler(this, &RubiksCubeSimulator::rotateBButton_Click);
			// 
			// rotateLButton
			// 
			this->rotateLButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rotateLButton->Location = System::Drawing::Point(307, 91);
			this->rotateLButton->Name = L"rotateLButton";
			this->rotateLButton->Size = System::Drawing::Size(70, 38);
			this->rotateLButton->TabIndex = 7;
			this->rotateLButton->Text = L"Rotate";
			this->rotateLButton->UseVisualStyleBackColor = true;
			this->rotateLButton->Click += gcnew System::EventHandler(this, &RubiksCubeSimulator::rotateLButton_Click);
			// 
			// rotateDButton
			// 
			this->rotateDButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rotateDButton->Location = System::Drawing::Point(383, 91);
			this->rotateDButton->Name = L"rotateDButton";
			this->rotateDButton->Size = System::Drawing::Size(74, 38);
			this->rotateDButton->TabIndex = 7;
			this->rotateDButton->Text = L"Rotate";
			this->rotateDButton->UseVisualStyleBackColor = true;
			this->rotateDButton->Click += gcnew System::EventHandler(this, &RubiksCubeSimulator::rotateDButton_Click);
			// 
			// reverseRButton
			// 
			this->reverseRButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->reverseRButton->Location = System::Drawing::Point(79, 135);
			this->reverseRButton->Name = L"reverseRButton";
			this->reverseRButton->Size = System::Drawing::Size(70, 41);
			this->reverseRButton->TabIndex = 7;
			this->reverseRButton->Text = L"Reverse";
			this->reverseRButton->UseVisualStyleBackColor = true;
			this->reverseRButton->Click += gcnew System::EventHandler(this, &RubiksCubeSimulator::reverseRButton_Click);
			// 
			// reverseUButton
			// 
			this->reverseUButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->reverseUButton->Location = System::Drawing::Point(155, 135);
			this->reverseUButton->Name = L"reverseUButton";
			this->reverseUButton->Size = System::Drawing::Size(70, 41);
			this->reverseUButton->TabIndex = 7;
			this->reverseUButton->Text = L"Reverse";
			this->reverseUButton->UseVisualStyleBackColor = true;
			this->reverseUButton->Click += gcnew System::EventHandler(this, &RubiksCubeSimulator::reverseUButton_Click);
			// 
			// reverseBButton
			// 
			this->reverseBButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->reverseBButton->Location = System::Drawing::Point(231, 135);
			this->reverseBButton->Name = L"reverseBButton";
			this->reverseBButton->Size = System::Drawing::Size(70, 41);
			this->reverseBButton->TabIndex = 7;
			this->reverseBButton->Text = L"Reverse";
			this->reverseBButton->UseVisualStyleBackColor = true;
			this->reverseBButton->Click += gcnew System::EventHandler(this, &RubiksCubeSimulator::reverseBButton_Click);
			// 
			// reverseLButton
			// 
			this->reverseLButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->reverseLButton->Location = System::Drawing::Point(307, 135);
			this->reverseLButton->Name = L"reverseLButton";
			this->reverseLButton->Size = System::Drawing::Size(70, 41);
			this->reverseLButton->TabIndex = 7;
			this->reverseLButton->Text = L"Reverse";
			this->reverseLButton->UseVisualStyleBackColor = true;
			this->reverseLButton->Click += gcnew System::EventHandler(this, &RubiksCubeSimulator::reverseLButton_Click);
			// 
			// reverseDButton
			// 
			this->reverseDButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->reverseDButton->Location = System::Drawing::Point(383, 135);
			this->reverseDButton->Name = L"reverseDButton";
			this->reverseDButton->Size = System::Drawing::Size(74, 41);
			this->reverseDButton->TabIndex = 7;
			this->reverseDButton->Text = L"Reverse";
			this->reverseDButton->UseVisualStyleBackColor = true;
			this->reverseDButton->Click += gcnew System::EventHandler(this, &RubiksCubeSimulator::reverseDButton_Click);
			// 
			// tableLayoutPanel6
			// 
			this->tableLayoutPanel6->ColumnCount = 1;
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel9, 0, 3);
			this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel7, 0, 0);
			this->tableLayoutPanel6->Controls->Add(this->resetButton, 0, 1);
			this->tableLayoutPanel6->Controls->Add(this->labelHtm, 0, 5);
			this->tableLayoutPanel6->Controls->Add(this->labelQtm, 0, 6);
			this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel8, 0, 4);
			this->tableLayoutPanel6->Controls->Add(this->solveButton, 0, 2);
			this->tableLayoutPanel6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel6->Location = System::Drawing::Point(624, 3);
			this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
			this->tableLayoutPanel6->RowCount = 7;
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 19.9992F)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 19.9992F)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 19.9992F)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 19.9992F)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20.00319F)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel6->Size = System::Drawing::Size(151, 179);
			this->tableLayoutPanel6->TabIndex = 3;
			// 
			// tableLayoutPanel7
			// 
			this->tableLayoutPanel7->ColumnCount = 3;
			this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				20)));
			this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel7->Controls->Add(this->label10, 1, 0);
			this->tableLayoutPanel7->Controls->Add(this->sizeTextBox, 2, 0);
			this->tableLayoutPanel7->Controls->Add(this->checkBox1, 0, 0);
			this->tableLayoutPanel7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel7->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel7->Name = L"tableLayoutPanel7";
			this->tableLayoutPanel7->RowCount = 1;
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel7->Size = System::Drawing::Size(145, 21);
			this->tableLayoutPanel7->TabIndex = 0;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label10->Location = System::Drawing::Point(23, 0);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(56, 21);
			this->label10->TabIndex = 0;
			this->label10->Text = L"size";
			this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// sizeTextBox
			// 
			this->sizeTextBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->sizeTextBox->Location = System::Drawing::Point(85, 3);
			this->sizeTextBox->Name = L"sizeTextBox";
			this->sizeTextBox->Size = System::Drawing::Size(57, 22);
			this->sizeTextBox->TabIndex = 1;
			this->sizeTextBox->Text = L"3";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Location = System::Drawing::Point(3, 3);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(14, 14);
			this->checkBox1->TabIndex = 2;
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &RubiksCubeSimulator::checkBox1_CheckedChanged);
			// 
			// resetButton
			// 
			this->resetButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->resetButton->Location = System::Drawing::Point(3, 30);
			this->resetButton->Name = L"resetButton";
			this->resetButton->Size = System::Drawing::Size(145, 21);
			this->resetButton->TabIndex = 1;
			this->resetButton->Text = L"Reset";
			this->resetButton->UseVisualStyleBackColor = true;
			this->resetButton->Click += gcnew System::EventHandler(this, &RubiksCubeSimulator::resetButton_Click);
			// 
			// shufflrButton
			// 
			this->shufflrButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->shufflrButton->Location = System::Drawing::Point(3, 3);
			this->shufflrButton->Name = L"shufflrButton";
			this->shufflrButton->Size = System::Drawing::Size(107, 21);
			this->shufflrButton->TabIndex = 1;
			this->shufflrButton->Text = L"Shuffle";
			this->shufflrButton->UseVisualStyleBackColor = true;
			this->shufflrButton->Click += gcnew System::EventHandler(this, &RubiksCubeSimulator::shufflrButton_Click);
			// 
			// solveButton
			// 
			this->solveButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->solveButton->Location = System::Drawing::Point(3, 57);
			this->solveButton->Name = L"solveButton";
			this->solveButton->Size = System::Drawing::Size(145, 21);
			this->solveButton->TabIndex = 1;
			this->solveButton->Text = L"Solve";
			this->solveButton->UseVisualStyleBackColor = true;
			this->solveButton->Click += gcnew System::EventHandler(this, &RubiksCubeSimulator::solveButton_Click);
			// 
			// labelHtm
			// 
			this->labelHtm->AutoSize = true;
			this->labelHtm->Dock = System::Windows::Forms::DockStyle::Fill;
			this->labelHtm->Location = System::Drawing::Point(3, 135);
			this->labelHtm->Name = L"labelHtm";
			this->labelHtm->Size = System::Drawing::Size(145, 20);
			this->labelHtm->TabIndex = 2;
			this->labelHtm->Text = L"HTM: 0";
			this->labelHtm->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelQtm
			// 
			this->labelQtm->AutoSize = true;
			this->labelQtm->Dock = System::Windows::Forms::DockStyle::Fill;
			this->labelQtm->Location = System::Drawing::Point(3, 155);
			this->labelQtm->Name = L"labelQtm";
			this->labelQtm->Size = System::Drawing::Size(145, 24);
			this->labelQtm->TabIndex = 3;
			this->labelQtm->Text = L"QTM: 0";
			this->labelQtm->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// tableLayoutPanel8
			// 
			this->tableLayoutPanel8->ColumnCount = 2;
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel8->Controls->Add(this->undoButton, 0, 0);
			this->tableLayoutPanel8->Controls->Add(this->redoButton, 1, 0);
			this->tableLayoutPanel8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel8->Location = System::Drawing::Point(0, 108);
			this->tableLayoutPanel8->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel8->Name = L"tableLayoutPanel8";
			this->tableLayoutPanel8->RowCount = 1;
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel8->Size = System::Drawing::Size(151, 27);
			this->tableLayoutPanel8->TabIndex = 4;
			// 
			// undoButton
			// 
			this->undoButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->undoButton->Location = System::Drawing::Point(3, 3);
			this->undoButton->Name = L"undoButton";
			this->undoButton->Size = System::Drawing::Size(69, 21);
			this->undoButton->TabIndex = 0;
			this->undoButton->Text = L"Undo";
			this->undoButton->UseVisualStyleBackColor = true;
			this->undoButton->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &RubiksCubeSimulator::undoButton_MouseDown);
			this->undoButton->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &RubiksCubeSimulator::undoButton_MouseUp);
			// 
			// redoButton
			// 
			this->redoButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->redoButton->Location = System::Drawing::Point(78, 3);
			this->redoButton->Name = L"redoButton";
			this->redoButton->Size = System::Drawing::Size(70, 21);
			this->redoButton->TabIndex = 1;
			this->redoButton->Text = L"Redo";
			this->redoButton->UseVisualStyleBackColor = true;
			this->redoButton->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &RubiksCubeSimulator::redoButton_MouseDown);
			this->redoButton->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &RubiksCubeSimulator::redoButton_MouseUp);
			// 
			// tableLayoutPanel9
			// 
			this->tableLayoutPanel9->ColumnCount = 2;
			this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				75)));
			this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel9->Controls->Add(this->shufflrButton, 0, 0);
			this->tableLayoutPanel9->Controls->Add(this->textBox1, 1, 0);
			this->tableLayoutPanel9->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel9->Location = System::Drawing::Point(0, 81);
			this->tableLayoutPanel9->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel9->Name = L"tableLayoutPanel9";
			this->tableLayoutPanel9->RowCount = 1;
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel9->Size = System::Drawing::Size(151, 27);
			this->tableLayoutPanel9->TabIndex = 0;
			// 
			// textBox1
			// 
			this->textBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox1->Location = System::Drawing::Point(116, 3);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(32, 22);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"100";
			// 
			// RubiksCubeSimulator
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 761);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Name = L"RubiksCubeSimulator";
			this->Text = L"RubiksCubeSimulator";
			this->Shown += gcnew System::EventHandler(this, &RubiksCubeSimulator::RubiksCubeSimulator_Shown);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			this->tableLayoutPanel5->ResumeLayout(false);
			this->tableLayoutPanel5->PerformLayout();
			this->tableLayoutPanel6->ResumeLayout(false);
			this->tableLayoutPanel6->PerformLayout();
			this->tableLayoutPanel7->ResumeLayout(false);
			this->tableLayoutPanel7->PerformLayout();
			this->tableLayoutPanel8->ResumeLayout(false);
			this->tableLayoutPanel9->ResumeLayout(false);
			this->tableLayoutPanel9->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void RubiksCubeSimulator_Shown(System::Object^  sender, System::EventArgs^  e) {
		this->draw();
	}
	private: System::Void panel1_Resize(System::Object^  sender, System::EventArgs^  e) {
		this->resize();
		this->draw();
	}
	private: System::Void rotateButton_Click(System::Object^  sender, System::EventArgs^  e) {
		int type = 0, column = 1, angle = 1;
		try {
			type = int::Parse(typeTextBox->Text);
		} catch (System::FormatException^ e) { }
		try {
			column = int::Parse(columnTextBox->Text);
		} catch (System::FormatException^ e) {}
		try {
			angle = int::Parse(angleTextBox->Text);
		} catch (System::FormatException^ e) {}
		cube->Rotate(type, column, angle);
		this->initTexture();
		this->draw();
	}
private: System::Void rotateFButton_Click(System::Object^  sender, System::EventArgs^  e) {
	try {
		cube->Rotate(0, int::Parse(textBoxF->Text), 1);
		this->initTexture();
		this->draw();
	}
	catch (System::FormatException^ e) {}
}
private: System::Void rotateRButton_Click(System::Object^  sender, System::EventArgs^  e) {
	try {
		cube->Rotate(1, int::Parse(textBoxR->Text), 1);
		this->initTexture();
		this->draw();
	}
	catch (System::FormatException^ e) {}
}
private: System::Void rotateUButton_Click(System::Object^  sender, System::EventArgs^  e) {
	try {
		cube->Rotate(2, int::Parse(textBoxU->Text), 1);
		this->initTexture();
		this->draw();
	}
	catch (System::FormatException^ e) {}
}
private: System::Void rotateBButton_Click(System::Object^  sender, System::EventArgs^  e) {
	try {
		cube->Rotate(3, int::Parse(textBoxB->Text), 1);
		this->initTexture();
		this->draw();
	}
	catch (System::FormatException^ e) {}
}
private: System::Void rotateLButton_Click(System::Object^  sender, System::EventArgs^  e) {
	try {
		cube->Rotate(4, int::Parse(textBoxL->Text), 1);
		this->initTexture();
		this->draw();
	}
	catch (System::FormatException^ e) {}
}
private: System::Void rotateDButton_Click(System::Object^  sender, System::EventArgs^  e) {
	try {
		cube->Rotate(5, int::Parse(textBoxD->Text), 1);
		this->initTexture();
		this->draw();
	}
	catch (System::FormatException^ e) {}
}
private: System::Void reverseFButton_Click(System::Object^  sender, System::EventArgs^  e) {
	try {
		cube->Rotate(0, int::Parse(textBoxF->Text), 3);
		this->initTexture();
		this->draw();
	}
	catch (System::FormatException^ e) {}
}
private: System::Void reverseRButton_Click(System::Object^  sender, System::EventArgs^  e) {
	try {
		cube->Rotate(1, int::Parse(textBoxR->Text), 3);
		this->initTexture();
		this->draw();
	}
	catch (System::FormatException^ e) {}
}
private: System::Void reverseUButton_Click(System::Object^  sender, System::EventArgs^  e) {
	try {
		cube->Rotate(2, int::Parse(textBoxU->Text), 3);
		this->initTexture();
		this->draw();
	}
	catch (System::FormatException^ e) {}
}
private: System::Void reverseBButton_Click(System::Object^  sender, System::EventArgs^  e) {
	try {
		cube->Rotate(3, int::Parse(textBoxB->Text), 3);
		this->initTexture();
		this->draw();
	}
	catch (System::FormatException^ e) {}
}
private: System::Void reverseLButton_Click(System::Object^  sender, System::EventArgs^  e) {
	try {
		cube->Rotate(4, int::Parse(textBoxL->Text), 3);
		this->initTexture();
		this->draw();
	}
	catch (System::FormatException^ e) {}
}
private: System::Void reverseDButton_Click(System::Object^  sender, System::EventArgs^  e) {
	try {
		cube->Rotate(5, int::Parse(textBoxD->Text), 3);
		this->initTexture();
		this->draw();
	}
	catch (System::FormatException^ e) {}
}
private: System::Void resetButton_Click(System::Object^  sender, System::EventArgs^  e) {
	int size = cube->size;
	try {
		size = int::Parse(sizeTextBox->Text);
	}
	catch (System::FormatException^ e) {}
	if (size == cube->size) {
		cube->Reset();
	}
	else {
		delete cube;
		cube = new RubiksCube(size);
	}
	this->initTexture();
	this->draw();
}
private: System::Void shufflrButton_Click(System::Object^  sender, System::EventArgs^  e) {
	try {
		cube->Shuffle(int::Parse(textBox1->Text));
		this->initTexture();
		this->draw();
	}
	catch (System::FormatException^ e) {}
}
delegate void BoolArgReturningVoidDelegate(bool enable);
delegate void VoidDelegate();
void SetEnable(bool enable) {
	if (this->tableLayoutPanel4->InvokeRequired) {
		this->Invoke(gcnew BoolArgReturningVoidDelegate(this, &RubiksCubeSimulator::SetEnable), enable);
	}
	else {
		this->tableLayoutPanel4->Enabled = enable;
	}
}
void UpdateHTM() {
	if (this->labelHtm->InvokeRequired) {
		this->Invoke(gcnew VoidDelegate(this, &RubiksCubeSimulator::UpdateHTM));
	} else {
		this->labelHtm->Text = "HTM: " + cube->htm;
	}
}
void UpdateQTM() {
	if (this->labelQtm->InvokeRequired) {
		this->Invoke(gcnew VoidDelegate(this, &RubiksCubeSimulator::UpdateQTM));
	}
	else {
		this->labelQtm->Text = "QTM: " + cube->qtm;
	}
}
private: System::Void SolveCube() {
	SetEnable(false);
	cube->Solve();
	this->initTexture();
	this->draw();
	SetEnable(true);
}
private: System::Void solveButton_Click(System::Object^  sender, System::EventArgs^  e) {
	//Solve();
	System::Threading::Thread^ solveThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &RubiksCubeSimulator::SolveCube));
	solveThread->Start();
}
private: System::Void panel1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (mouseDown) {
		mouseMove(e->X - previousMousePositionX, e->Y - previousMousePositionY);
		previousMousePositionX = e->X;
		previousMousePositionY = e->Y;
	}
}
private: System::Void panel1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	previousMousePositionX = e->X;
	previousMousePositionY = e->Y;
	mouseDown = true;
}
private: System::Void panel1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	mouseDown = false;
}
private: System::Void panel1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Delta< 0) {
		zoom += 0.1;
	}
	else {
		zoom -= 0.1;
	}
	mouseMove(0, 0);
}
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	this->draw();
}
private: System::Void redoButton_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	cube->Redo();
	this->initTexture();
	this->draw();
	this->redoTimer->Interval = 1000;
	this->redoTimer->Enabled = true;
}
private: System::Void redoButton_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	this->redoTimer->Enabled = false;
}
private: System::Void redoTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
	cube->Redo();
	this->initTexture();
	this->draw();
	this->redoTimer->Interval = 100;
}
private: System::Void undoButton_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	cube->Undo();
	this->initTexture();
	this->draw();
	this->undoTimer->Interval = 1000;
	this->undoTimer->Enabled = true;
}
private: System::Void undoButton_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	this->undoTimer->Enabled = false;
}
private: System::Void undoTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
	cube->Undo();
	this->initTexture();
	this->draw();
	this->undoTimer->Interval = 100;
}
};
}
