#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H


//        QString Projected = "Projection(1:YES;2:NO) :" + QString::number(poDataset->GetSpatialRef()->IsProjected());
//        QString SemiMajor = "长轴半径 = " + QString::number(poDataset->GetSpatialRef()->GetSemiMajor(),'f',0);
//        QString SemiMinor = "短轴半径 = " + QString::number(poDataset->GetSpatialRef()->GetSemiMinor(),'f',9);
//        QString GetInvFlattening = "扁率 = " + QString::number(poDataset->GetSpatialRef()->GetInvFlattening(),'f',9);
//        double test[6];
//        poDataset->GetGeoTransform(test);
//        ui->plainTextEdit->appendPlainText(pic + "TIF");
//        ui->plainTextEdit->appendPlainText(Projected);
//        ui->plainTextEdit->appendPlainText(SemiMajor);
//        ui->plainTextEdit->appendPlainText(SemiMinor);
//        ui->plainTextEdit->appendPlainText(GetInvFlattening);
        //upleft Coordinate
//        ui->plainTextEdit->appendPlainText("upperCoord = " + QString::number(test[0],'f',4));
//        ui->plainTextEdit->appendPlainText("leftCoord = " + QString::number(test[3],'f',4));
        //pixel width and height
//        ui->plainTextEdit->appendPlainText("pixel width = " + QString::number(test[1],'f',4));
//        ui->plainTextEdit->appendPlainText("pixel height = " + QString::number(test[5],'f',4));

        //proj信息
//        ui->plainTextEdit->appendPlainText("投影信息:" + QString(poDataset->GetSpatialRef()->GetAttrValue("PROJCS")));
//        ui->plainTextEdit->appendPlainText("投影信息:" + QString(poDataset->GetSpatialRef()->GetAttrValue("GEOGCS")));
//        ui->plainTextEdit->appendPlainText("投影信息:" + QString(poDataset->GetSpatialRef()->GetAttrValue("DATUM")));
//        ui->plainTextEdit->appendPlainText("投影信息:" + QString(poDataset->GetSpatialRef()->GetAttrValue("PRIMEM")));
//        ui->plainTextEdit->appendPlainText("投影信息:" + QString(poDataset->GetSpatialRef()->GetAttrValue("PROJECTION")));
/*
    //查询坐标系信息
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("PROJCS"));
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("GEOGCS"));
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("DATUM"));
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("PRIMEM"));
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("UNIT"));
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("AUTHORITY"));
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("PROJECTION"));
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("PARAMETER"));
//    qDebug(poDataset->GetSpatialRef()->GetAttrValue("AXIS"));

     //查询椭球信息
//    qDebug("projected :%d",poDataset->GetSpatialRef()->IsProjected());
//    qDebug("SemiMajor :%f",poDataset->GetSpatialRef()->GetSemiMajor());
//    qDebug("SemiMinor :%.9f",poDataset->GetSpatialRef()->GetSemiMinor());
//    qDebug("GetInvFlattening :%.9f",poDataset->GetSpatialRef()->GetInvFlattening());

    //查询偏移信息
//    qDebug("SRS_PP_CENTRAL_MERIDIAN %f",poDataset->GetSpatialRef()->GetProjParm(SRS_PP_CENTRAL_MERIDIAN,0.0));
//    qDebug("SRS_PP_STANDARD_PARALLEL_1 %f",poDataset->GetSpatialRef()->GetProjParm(SRS_PP_STANDARD_PARALLEL_1,0.0));
//    qDebug("SRS_PP_FALSE_EASTING %f",poDataset->GetSpatialRef()->GetProjParm(SRS_PP_FALSE_EASTING,0.0));
//    qDebug("SRS_PP_FALSE_NORTHING %f",poDataset->GetSpatialRef()->GetProjParm(SRS_PP_FALSE_NORTHING,0.0));

    //
//    qDebug("%f",poDataset->GetSpatialRef()->GetLinearUnits());

    //查询value范围
//    GDALRasterBand* poBand = poDataset->GetRasterBand(1);
//    int bGotMin,bGotMax;
//    double adfMinMax[2];
//    adfMinMax[0] = poBand->GetMinimum(&bGotMin);
//    adfMinMax[1] = poBand->GetMaximum(&bGotMax);
//    GDALComputeRasterMinMax((GDALRasterBandH)poBand,TRUE,adfMinMax);
//    qDebug("Min=%.3f,Max=%.3f",adfMinMax[0],adfMinMax[1]);


//    QString Projected = "Projection(1:YES;2:NO) :" + QString::number(poDataset->GetSpatialRef()->IsProjected());
//    QString SemiMajor = "长轴半径 = " + QString::number(poDataset->GetSpatialRef()->GetSemiMajor(),'f',0);
//    QString SemiMinor = "短轴半径 = " + QString::number(poDataset->GetSpatialRef()->GetSemiMinor(),'f',9);
//    QString GetInvFlattening = "扁率 = " + QString::number(poDataset->GetSpatialRef()->GetInvFlattening(),'f',9);
//    double test[6];
//    poDataset->GetGeoTransform(test);
//    ui->plainTextEdit->clear();
//    ui->plainTextEdit->appendPlainText(Projected);
//    ui->plainTextEdit->appendPlainText(SemiMajor);
//    ui->plainTextEdit->appendPlainText(SemiMinor);
//    ui->plainTextEdit->appendPlainText(GetInvFlattening);
//    //upleft Coordinate
//    ui->plainTextEdit->appendPlainText("upperCoord = " + QString::number(test[0],'f',4));
//    ui->plainTextEdit->appendPlainText("leftCoord = " + QString::number(test[3],'f',4));
//    //pixel width and height
//    ui->plainTextEdit->appendPlainText("pixel width = " + QString::number(test[1],'f',4));
//    ui->plainTextEdit->appendPlainText("pixel height = " + QString::number(test[5],'f',4));
//    //变形信息
////    ui->plainTextEdit->appendPlainText(QString::number(test[2],'f',4));
////    ui->plainTextEdit->appendPlainText(QString::number(test[4],'f',4));

//    //查询value范围
//    GDALDataset::Bands poBands = poDataset->GetBands();
//    for(int i=1;i<poBands.size()+1;i++){
//        GDALRasterBand* poBand = poDataset->GetRasterBand(i);
//        ui->plainTextEdit->appendPlainText("波段" + QString::number(i) + "最小值 : " + QString::number(getBandInfoMin(poBand).first()));
//        ui->plainTextEdit->appendPlainText("波段" + QString::number(i) + "最大值 : " + QString::number(getBandInfoMin(poBand).last()));
//    }

*/
