
#include <qfiledialog.h>
#include <qstring.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include "CommonUtils.h"



/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/


void Form1::fileNew()
{

}


void Form1::fileOpen()
{
	QString *qstring;
	printf("Opening File Dialog");
    //QString filename = QFileDialog::getOpenFileName(tr("*.ply"), tr("Ply Files (*.ply)"), NULL, "Add PLY", tr(""), qstring, true);
    //QString filename = QFileDialog::getOpenFileName(tr("*.ply"), tr("/"), NULL, "Add PLY", tr("../samples/range-scan/bunny/data/"), qstring, true);
//QFileDialog::getExistingDirectory(const QString&, QWidget*, const char*, const QString&, bool, bool)
    QString directory = QFileDialog::getExistingDirectory(tr("../samples/range-scan/bunny"), NULL, "Add RangScan Grouping", tr(""));
	printf("Open File Dialog finished");
    printf("Chosen file is %s", directory.latin1());

	std::cout << directory.latin1();

	//myGLWidget1->loadPlyFile(filename.latin1());
	myGLWidget1->loadPlyDirectory(directory.latin1());
}


void Form1::fileSave()
{

}


void Form1::fileSaveAs()
{

}


void Form1::filePrint()
{

}


void Form1::fileExit()
{
	exit(0);
}


void Form1::editUndo()
{

}


void Form1::editRedo()
{

}


void Form1::editCut()
{

}


void Form1::editCopy()
{

}


void Form1::editPaste()
{

}


void Form1::editFind()
{

}


void Form1::helpIndex()
{

}


void Form1::helpContents()
{

}


void Form1::helpAbout()
{

}


void Form1::Add_Scan_Button_clicked()
{
	QString *qstring;
    QString filename = QFileDialog::getOpenFileName(tr("."), tr("Ply Files (*.ply)"), NULL, "Add PLY", tr(""), qstring, true);
    printf("Chosen file is %s", filename);
	//static QString QFileDialog::getOpenFileName(const QString&, const QString&, QWidget*, const char*, const QString&, QString*, bool)

}

void Form1::Volfill_clicked()
{
	cout << "\r\nRunning volfill ..." << endl;
        runVolfill();
}


void Form1::Vrip_Prepare_clicked()
{
        cout << "\r\nRunning prepare vrip..." << endl;
        prepareVrip();
}


void Form1::Vrip_Merge_clicked()
{
        cout << "\r\nRunning vripnew ..." << endl;
        createNewVripVri();
}


void Form1::Vrip_Surf_clicked()
{
        cout << "\r\nRunning vripsurf..." << endl;
        createVripSurf();
}


void Form1::View_Mesh_clicked()
{
        cout << "\r\n Launch scanalyze ..." << endl;
        launchScanalyze();
}

void Form1::alignWithICP_Button_clicked()
{
        cout << "\r\n Running ICP ..." << endl;
        runICP(myGLWidget1->fileManager.getScanNames(),myGLWidget1->fileManager.getNumberFiles() );
	myGLWidget1->updateGL();
}


void Form1::scanAngle_valueChanged( int newAngle)
{
    scanGroupAngleLabel->setText(QString::number(newAngle));
    myGLWidget1->scanGroupAngleChanged(newAngle);
}


void Form1::myGLWidget1_destroyed( QObject * )
{

}
