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
			hDC = GetDC((HWND)(panel1->Handle.ToInt32()));
			hGLRC = initializeOpenGLContext(hDC);
			cube = new RubiksCube(3);
		}
		HGLRC initializeOpenGLContext(HDC hDC);
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
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(284, 261);
			this->panel1->TabIndex = 0;
			this->panel1->Resize += gcnew System::EventHandler(this, &RubiksCubeSimulator::panel1_Resize);
			// 
			// RubiksCubeSimulator
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->panel1);
			this->Name = L"RubiksCubeSimulator";
			this->Text = L"RubiksCubeSimulator";
			this->Shown += gcnew System::EventHandler(this, &RubiksCubeSimulator::RubiksCubeSimulator_Shown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void RubiksCubeSimulator_Shown(System::Object^  sender, System::EventArgs^  e) {
		this->draw();
	}
	private: System::Void panel1_Resize(System::Object^  sender, System::EventArgs^  e) {
		this->draw();
	}
	};
}
