#include "Lab1.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Lab1::Lab1 form;
	Application::Run(% form);
}

float** A, B;
int N1, M1, N2, M2;

// ������� 1
System::Void Lab1::Lab1::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	M1 = Convert::ToInt32(numericUpDown1->Value);
	N1 = Convert::ToInt32(numericUpDown2->Value);

	A = new float* [M1];
	for (int i = 0; i < M1; i++)
	{
		A[i] = new float[N1];
	}

	for (int i = 0; i < M1; i++)
	{
		for (int j = 0; j < N1; j++)
		{
			A[i][j] = 0;
		}
	}

	dataGridView1->RowCount = M1;
	dataGridView1->ColumnCount = N1;

	showA();

	//�������
	dataGridView1->AutoResizeRowHeadersWidth(DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders); //������
	dataGridView1->AutoResizeColumns(); //�������
	
	return System::Void();
}


void Lab1::Lab1::showA()
{
	for (int i = 0; i < M1; i++)
	{
		for (int j = 0; j < N1; j++)
		{
			// ����� ������ �������
			dataGridView1->Columns[j]->HeaderCell->Value = Convert::ToString(j + 1);

			// ����� ����� ������
			dataGridView1->Rows[i]->HeaderCell->Value = Convert::ToString(i + 1);

			// ����� �������
			dataGridView1->Rows[i]->Cells[j]->Value = A[i][j];
		}
	}
}

System::Void Lab1::Lab1::dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
	return System::Void();
}


System::Void Lab1::Lab1::numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}


System::Void Lab1::Lab1::numericUpDown2_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

// ������� 2
System::Void Lab1::Lab1::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}


System::Void Lab1::Lab1::dataGridView2_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
	return System::Void();
}


System::Void Lab1::Lab1::numericUpDown4_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}


System::Void Lab1::Lab1::numericUpDown3_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

// ������ ������� � ��������
System::Void Lab1::Lab1::button3_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}


System::Void Lab1::Lab1::button4_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

// ������ ����
System::Void Lab1::Lab1::�����ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();

	return System::Void();
}


System::Void Lab1::Lab1::����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("������� 1. �������:"
	"������� �����, � ������� ����������� ������� ��� ������ � ���������:"
	"�) ������� ���������� ������������ ������;"
	"�) ������� ���������� �������� ���� ������."
	"������ ��� ������� �������� �����������."
	"������������ ����������� � �����������, ����������� �����������."
	"���������� ������ ����������� ������, ���������� ��� �������.");

	return System::Void();
}




