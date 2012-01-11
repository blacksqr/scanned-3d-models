

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
    QString directory = QFileDialog::getExistingDirectory(tr("../samples/range-scan"), NULL, "Add RangScan Grouping", tr(""));	
    if ( directory.isNull() == false )
    {
	myGLWidget1->loadPlyDirectory(directory.latin1());
    }
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
	myGLWidget1->displaySingleMesh("/tmp/vrip-prep/filled-bun.ply");

        //cout << "\r\n Launch scanalyze ..." << endl;
        //launchScanalyze();
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


void Form1::translationSlider_valueChanged( int newTranslation)
{
    translationLabel->setText(QString::number(newTranslation));
    myGLWidget1->scanGroupTranslationChanged(newTranslation);
}


void Form1::pushButton9_released()
{
    scanGroupAngleLabel->setText(QString::number(360));
    myGLWidget1->scanGroupAngleChanged(360);
    scanAngle->setValue(360);

    translationLabel->setText(QString::number(0));
    myGLWidget1->scanGroupTranslationChanged(0);
    translationSlider->setValue(0);

	myGLWidget1->resetWidget();
	removeVripPrepDir();
}

void Form1::mergeScans()
{
	// STEP 1
    icpButton->setPaletteBackgroundColor(QColor( 228, 85, 3 ));
	icpButton->repaint();
	myGLWidget1->updateGL();

    runICP(myGLWidget1->fileManager.getScanNames(),myGLWidget1->fileManager.getNumberFiles() );
	myGLWidget1->updateGL();

    icpButton->setPaletteBackgroundColor(QColor( 221, 223, 228));
	icpButton->repaint();
	myGLWidget1->updateGL();

	// STEP 2
    vripPrepareButton->setPaletteBackgroundColor( QColor( 228, 85, 3));
	vripPrepareButton->repaint();
	myGLWidget1->updateGL();

    prepareVrip();

    vripPrepareButton->setPaletteBackgroundColor( QColor( 221, 223, 228));
	vripPrepareButton->repaint();
	myGLWidget1->updateGL();

	// STEP 3
    vripMergeButton->setPaletteBackgroundColor( QColor(228, 85, 3));
	vripMergeButton->repaint();
	myGLWidget1->updateGL();

    createNewVripVri();

    vripMergeButton->setPaletteBackgroundColor( QColor(221, 223, 228));
	vripMergeButton->repaint();
	myGLWidget1->updateGL();

	// STEP 4
	if(enableVolfillButton->isChecked() == true)
	{
    	volfillButton->setPaletteBackgroundColor( QColor(228, 85, 3));
		volfillButton->repaint();
		myGLWidget1->updateGL();

    	runVolfill();

    	volfillButton->setPaletteBackgroundColor( QColor(221, 223, 228));
		volfillButton->repaint();
		myGLWidget1->updateGL();
    }

	// STEP 5
    vripSurfaceButton->setPaletteBackgroundColor( QColor(228, 85, 3));
	vripSurfaceButton->repaint();
	myGLWidget1->updateGL();

    createVripSurf();

    vripSurfaceButton->setPaletteBackgroundColor( QColor(221, 223, 228));
	vripSurfaceButton->repaint();
	myGLWidget1->updateGL();

	// STEP 6
    viewNewMeshButton->setPaletteBackgroundColor( QColor(228, 85, 3));
	viewNewMeshButton->repaint();
	myGLWidget1->updateGL();

	myGLWidget1->displaySingleMesh("/tmp/vrip-prep/filled-bun.ply");

    viewNewMeshButton->setPaletteBackgroundColor( QColor(221, 223, 228));
	viewNewMeshButton->repaint();
	myGLWidget1->updateGL();
}


void Form1::enableVolfillButton_toggled( bool enabled)
{
	volfillButton->setEnabled(enabled);
}
