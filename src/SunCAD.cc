#include <wx/wx.h>

// ��Ӧ���࣬�̳��� wxApp
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

// �������࣬�̳��� wxFrame
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
};

// Ϊ��Ӧ����ʵ�� `wxIMPLEMENT_APP`
wxIMPLEMENT_APP(MyApp);

// ��ʼ��Ӧ��
bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("Hello wxWidgets");  // ����������
    frame->Show(true);  // ��ʾ������
    return true;
}

// �����ڵĹ��캯��
MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title) {
    // �����˵���
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(1, "&Hello...\tCtrl-H", "Show Hello message");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");

    SetMenuBar(menuBar);

    // ���¼�
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, 1);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
}

// "Hello" �˵����¼�����
void MyFrame::OnHello(wxCommandEvent& event) {
    wxLogMessage("Hello, wxWidgets!");
}

// "Exit" �˵����¼�����
void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);  // �رմ���
}
