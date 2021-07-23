#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <vector>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Проект станции технического обслуживания");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    double tk = (ui->line_time->text()).toInt()*60;
    int kol; int i=0;
    double st = 0, p, s_to=0, s_pr=0, s_sr=0, s_sl=0, SUM;
    int j=0, r1=0, r2=0, r3=0, k=1, l=1,m=1,n=1;
    double t_to=0, t_pr=0, t_sr=0, t_sl=0, allTime;
    double pr_to, pr_rem, pr_torem, pr_r1, pr_r2, pr;
    pr_to = (ui->line_pr_to->text()).toInt();//36%
    pr_to = pr_to/100;
    pr_rem = (ui->line_pr_rem->text()).toInt();//64%
    pr_rem = pr_rem/100;
    pr_torem = (ui->line_pr_torem->text()).toInt();//12%
    pr_torem = pr_torem/100;

    pr = pr_rem/3;
    pr_r1 = pr_to + pr;
    pr_r2 = pr_r1 + pr;

    std::vector<double> vecPrib;
    std::vector<double> vecObsl;
   // std::vector<int> vecOch;
    std::vector<int> vecBloc;


    QString new_label;

  //  new_label = QString::number(tk, 'g', 15);
  //  ui->line_time->setText(new_label);


// Генерируем время поступления машин (double)(
    while (st <= tk) {
          p = -log(((double)rand() / RAND_MAX)*((double)rand() / RAND_MAX)) * 14;
          st = st + p;
          vecPrib.push_back(st);
          i++;
    }
    kol=i;

    new_label = QString::number(kol, 'g', 15);
    ui->label_kol->setText(new_label);

// распределение по типу обслуживания
    for (i=1; i<=kol; i++) {
        p=(double)(rand())/RAND_MAX;// / 32767;
        if (p<=pr_torem) {j++; r2++; vecBloc.push_back(4);}//0.12
        else if ((p>pr_torem) & (p<=pr_to)) {j++; vecBloc.push_back(0);}//0.12-0.36
        else if ((p>pr_to) & (p<=pr_r1)) {r1++; vecBloc.push_back(1);} //0.36-0.57
        else if ((p>pr_r1) & (p<=pr_r2)) {r2++; vecBloc.push_back(2);}//0.57-0.78
        else {r3++; vecBloc.push_back(3);}
    }

    new_label = QString::number(j, 'g', 15);
    ui->label_j->setText(new_label);

    new_label = QString::number(r1, 'g', 15);
    ui->label_r1->setText(new_label);

    new_label = QString::number(r2, 'g', 15);
    ui->label_r2->setText(new_label);

    new_label = QString::number(r3, 'g', 15);
    ui->label_r3->setText(new_label);


// генерируем время обслуживания на блоках и его стоимость
    std::vector<int> block0;
    while (k<=j)
    {
    p= 100+(400-100)*((double)rand() / RAND_MAX);//100-400
    s_to=s_to+p;
    p= 10+(55-10)*((double)rand() / RAND_MAX);//10-55
    t_to=t_to+p;
    block0.push_back(p);
    k++;
    }
    if (t_to/j >0) {t_to=t_to/j;}

    new_label = QString::number(s_to, 'f', 2);
    ui->label_s_to->setText(new_label);
    new_label = QString::number(t_to, 'f', 2);
    ui->label_t_to->setText(new_label);

    std::vector<int> block1;
    while (l<=r1)
     {
     p= 50+(450-50)*((double)rand() / RAND_MAX);//50-450
     s_pr=s_pr+p;
     p= 12+(45-12)*((double)rand() / RAND_MAX);//12-45
     t_pr=t_pr+p;
     block1.push_back(p);
     l++;
     }
    if (t_pr/r1 > 0) {t_pr=t_pr/r1;}

    new_label = QString::number(s_pr, 'f', 2);
    ui->label_s_pr->setText(new_label);
    new_label = QString::number(t_pr, 'f', 2);
    ui->label_t_pr->setText(new_label);

    std::vector<int> block2;
    while (m<=r2)
    {
    p=10 +(1400-100)*((double)rand() / RAND_MAX);//100-1400
    s_sr=s_sr+p;
    p = 45+5.0*((double)rand()/ RAND_MAX);
    //ср-45, сркв откл -5
    t_sr=t_sr+p;
    block2.push_back(p);
    m++;
    }
    if (t_sr/r2 > 0) {t_sr/=r2;}

    new_label = QString::number(s_sr, 'f', 2);
    ui->label_s_sr->setText(new_label);
    new_label = QString::number(t_sr, 'f', 2);
    ui->label_t_sr->setText(new_label);

    std::vector<int> block3;
    while (n<=r3)
    {
    p=350+(2550-350)*((double)rand() / RAND_MAX);//350-2550
    s_sl=s_sl+p;
    p= 80+(150-80)*((double)rand() / RAND_MAX);//80-150
    t_sl=t_sl+p;
    block3.push_back(p);
    n++;
    }
    if (t_sl/r3 > 0) {t_sl=t_sl/r3;}

    new_label = QString::number(s_sl, 'f', 2);
    ui->label_s_sl->setText(new_label);
    new_label = QString::number(t_sl, 'f', 2);
    ui->label_t_sl->setText(new_label);


    SUM=s_to+s_pr+s_sr+s_sl;
    new_label = QString::number(SUM, 'f', 2);
    ui->label_sum->setText(new_label);
    allTime=(t_to*j+t_pr*r1+t_sr*r2+t_sl*r3)/kol;
    new_label = QString::number(allTime, 'f',2);
    ui->label_allTime->setText(new_label);

//------------Рассчитываем очереди--------------------------
    int kolBlock, toBlock, remBlock;
    toBlock = (ui->line_kol_to->text()).toInt();
    remBlock = (ui->line_kol_rem->text()).toInt();
       // std::cin >> toBlock >> remBlock;
    kolBlock = toBlock + remBlock;
    double blockTO_1=0, blockTO_2=0, blockRem_1=0, blockRem_2=0, blockRem_3=0, blockRem_4=0;
    int ochBlockTO_1=0, ochBlockTO_2=0, ochBlockRem_1=0, ochBlockRem_2=0, ochBlockRem_3=0, ochBlockRem_4=0;
    int maxOchBlockTO_1=0, maxOchBlockTO_2=0, maxOchBlockRem_1=0, maxOchBlockRem_2=0, maxOchBlockRem_3=0, maxOchBlockRem_4=0;
    int k0=0, k1=0, k2=0, k3=0;



    for (int i = 0; i < kol; i++) {
      if (vecBloc[i] == 0) {
        if ((blockTO_1 <= vecPrib[i]) || (blockTO_2 <= vecPrib[i])) {
          if (blockTO_1 <= vecPrib[i]) {
            blockTO_1 = vecPrib[i] + block0[k0];
            k0++;
            ochBlockTO_1 = 0;
          }
          else {
            if (blockTO_2 <= vecPrib[i]) {
              blockTO_2 = vecPrib[i] + block0[k0];
              k0++;
              ochBlockTO_2 = 0;
            }
          }
        }
        else {
          if (blockTO_1 <= blockTO_2) {
            ochBlockTO_1++;
            blockTO_1 += block0[k0];
            k0++;
          }
          else {
            ochBlockTO_2++;
            blockTO_2 += block0[k0];
            k0++;
          }
        }
      //  std::cout << blockTO_1 << " " << blockTO_2 << " " << ochBlockTO_1 << " " << ochBlockTO_2 << " " <<i<< " \n";

        maxOchBlockTO_1 = std::max(ochBlockTO_1, maxOchBlockTO_1);
        maxOchBlockTO_2 = std::max(ochBlockTO_2, maxOchBlockTO_2);
      }
    if (kolBlock == 5) {
      if (vecBloc[i] == 1) {
        if ((blockRem_1 <= vecPrib[i]) || (blockRem_2 <= vecPrib[i]) || (blockRem_3 <= vecPrib[i])) {
          if (blockRem_1 <= vecPrib[i]) {
            blockRem_1 = vecPrib[i] + block1[k1];
            k1++;
            ochBlockRem_1 = 0;
          }
          else {
            if (blockRem_2 <= vecPrib[i]) {
              blockRem_2 = vecPrib[i] + block1[k1];
              k1++;
              ochBlockRem_2 = 0;
            }
            else {
              if (blockRem_3 <= vecPrib[i]) {
                blockRem_3 = vecPrib[i] + block1[k1];
                k1++;
                ochBlockRem_3 = 0;
              }
            }
          }
        }
        else {
          if ((blockRem_1 <= blockRem_2) && (blockRem_1 <= blockRem_3)) {
            ochBlockRem_1++;
            blockRem_1 += block1[k1];
            k1++;
          }
          else {
            if ((blockRem_2 < blockRem_1) && (blockRem_2 <= blockRem_3)) {
              ochBlockRem_2++;
              blockRem_2 += block1[k1];
              k1++;
            }
            else {
              if ((blockRem_3 < blockRem_1) && (blockRem_3 < blockRem_2)) {
                ochBlockRem_3++;
                blockRem_3 += block1[k1];
                k1++;
              }
            }
          }
        }
      //  std::cout << blockRem_1 << " " << blockRem_2 << " " << blockRem_3 << " " << ochBlockRem_1 << " " << ochBlockRem_2 << " " << ochBlockRem_3 << " " << i << " \n";

        maxOchBlockRem_1 = std::max(ochBlockRem_1, maxOchBlockRem_1);
        maxOchBlockRem_2 = std::max(ochBlockRem_2, maxOchBlockRem_2);
        maxOchBlockRem_3 = std::max(ochBlockRem_3, maxOchBlockRem_3);
      }

      if (vecBloc[i] == 2) {
        if ((blockRem_1 <= vecPrib[i]) || (blockRem_2 <= vecPrib[i]) || (blockRem_3 <= vecPrib[i])) {
          if (blockRem_1 <= vecPrib[i]) {
            blockRem_1 = vecPrib[i] + block2[k2];
            k2++;
            ochBlockRem_1 = 0;
          }
          else {
            if (blockRem_2 <= vecPrib[i]) {
              blockRem_2 = vecPrib[i] + block2[k2];
              k2++;
              ochBlockRem_2 = 0;
            }
            else {
              if (blockRem_3 <= vecPrib[i]) {
                blockRem_3 = vecPrib[i] + block2[k2];
                k2++;
                ochBlockRem_3 = 0;
              }
            }
          }
        }
        else {
          if ((blockRem_1 <= blockRem_2) && (blockRem_1 <= blockRem_3)) {
            ochBlockRem_1++;
            blockRem_1 += block2[k2];
            k2++;
          }
          else {
            if ((blockRem_2 < blockRem_1) && (blockRem_2 <= blockRem_3)) {
              ochBlockRem_2++;
              blockRem_2 += block2[k2];
              k2++;
            }
            else {
              if ((blockRem_3 < blockRem_1) && (blockRem_3 < blockRem_2)) {
                ochBlockRem_3++;
                blockRem_3 += block2[k2];
                k2++;
              }
            }
          }
        }
      //  std::cout << blockRem_1 << " " << blockRem_2 << " " << blockRem_3 << " " << ochBlockRem_1 << " " << ochBlockRem_2 << " " << ochBlockRem_3 << " " << i << " \n";

        maxOchBlockRem_1 = std::max(ochBlockRem_1, maxOchBlockRem_1);
        maxOchBlockRem_2 = std::max(ochBlockRem_2, maxOchBlockRem_2);
        maxOchBlockRem_3 = std::max(ochBlockRem_3, maxOchBlockRem_3);
      }

      if (vecBloc[i] == 3) {
        if ((blockRem_1 <= vecPrib[i]) || (blockRem_2 <= vecPrib[i]) || (blockRem_3 <= vecPrib[i])) {
          if (blockRem_1 <= vecPrib[i]) {
            blockRem_1 = vecPrib[i] + block3[k3];
            k3++;
            ochBlockRem_1 = 0;
          }
          else {
            if (blockRem_2 <= vecPrib[i]) {
              blockRem_2 = vecPrib[i] + block3[k3];
              k3++;
              ochBlockRem_2 = 0;
            }
            else {
              if (blockRem_3 <= vecPrib[i]) {
                blockRem_3 = vecPrib[i] + block3[k3];
                k3++;
                ochBlockRem_3 = 0;
              }
            }
          }
        }
        else {
          if ((blockRem_1 <= blockRem_2) && (blockRem_1 <= blockRem_3)) {
            ochBlockRem_1++;
            blockRem_1 += block3[k3];
            k3++;
          }
          else {
            if ((blockRem_2 < blockRem_1) && (blockRem_2 <= blockRem_3)) {
              ochBlockRem_2++;
              blockRem_2 += block3[k3];
              k3++;
            }
            else {
              if ((blockRem_3 < blockRem_1) && (blockRem_3 < blockRem_2)) {
                ochBlockRem_3++;
                blockRem_3 += block3[k3];
                k3++;
              }
            }
          }
        }
       // std::cout << blockRem_1 << " " << blockRem_2 << " " << blockRem_3 << " " << ochBlockRem_1 << " " << ochBlockRem_2 << " " << ochBlockRem_3 << " " << i << " \n";

        maxOchBlockRem_1 = std::max(ochBlockRem_1, maxOchBlockRem_1);
        maxOchBlockRem_2 = std::max(ochBlockRem_2, maxOchBlockRem_2);
        maxOchBlockRem_3 = std::max(ochBlockRem_3, maxOchBlockRem_3);
      }

      if (vecBloc[i] == 4) {
        if ((blockTO_1 <= vecPrib[i]) || (blockTO_2 <= vecPrib[i])) {
          if (blockTO_1 <= vecPrib[i]) {
            blockTO_1 = vecPrib[i] + block0[k0];
            vecPrib[i] += block0[k0];
            k0++;
            ochBlockTO_1 = 0;
          }
          else {
            if (blockTO_2 < vecPrib[i]) {
              blockTO_2 = vecPrib[i] + block0[k0];
              vecPrib[i] += block0[k0];
              k0++;
              ochBlockTO_2 = 0;
            }
          }
        }
        else {
          if (blockTO_1 <= blockTO_2) {
            ochBlockTO_1++;
            blockTO_1 += block0[k0];
            vecPrib[i] = blockTO_1;
            k0++;
          }
          else {
            ochBlockTO_2++;
            blockTO_2 += block0[k0];
            vecPrib[i] = blockTO_2;
            k0++;
          }
        }
        //std::cout << blockTO_1 << " " << blockTO_2 << " " << ochBlockTO_1 << " " << ochBlockTO_2 << " " << i << " \n";
        //std::cout << blockRem_1 << " " << blockRem_2 << " " << blockRem_3 << " " << ochBlockRem_1 << " " << ochBlockRem_2 << " " << ochBlockRem_3 << " " << i << " \n";

        maxOchBlockTO_1 = std::max(ochBlockTO_1, maxOchBlockTO_1);
        maxOchBlockTO_2 = std::max(ochBlockTO_2, maxOchBlockTO_2);
        //std::cout << blockTO_1 << " " << blockTO_2 << " " << ochBlockTO_1 << " " << ochBlockTO_2 << " " << i << " \n";
        vecBloc[i] = 2;
        int a = i, b;
        double tmp;
      //  std::cout << blockTO_1 << " " << blockTO_2 << " " << ochBlockTO_1 << " " << ochBlockTO_2 << " " << i << " \n";
        if (a < kol - 2) {
          while ((vecPrib[a] > vecPrib[a + 1]) && (a < kol - 2)) {
          tmp = vecPrib[a];
          vecPrib[a] = vecPrib[a + 1];
          vecPrib[a + 1] = tmp;
          b = vecBloc[a];
          vecBloc[a] = vecBloc[a + 1];
          vecBloc[a + 1] = b;
          //std::cout << a << " ";
          a++;
          //std::cout << a << " ";
          }
        }
       // std::cout << blockTO_1 << " " << blockTO_2 << " " << ochBlockTO_1 << " " << ochBlockTO_2 << " " << i << " \n";
        i--;

      }
    }
    if (kolBlock == 6) {
           if (vecBloc[i] == 1) {
             if ((blockRem_1 <= vecPrib[i]) || (blockRem_2 <= vecPrib[i]) || (blockRem_3 <= vecPrib[i]) || (blockRem_4 <= vecPrib[i])) {
               if (blockRem_1 <= vecPrib[i]) {
                 blockRem_1 = vecPrib[i] + block1[k1];
                 k1++;
                 ochBlockRem_1 = 0;
               }
               else {
                 if (blockRem_2 <= vecPrib[i]) {
                   blockRem_2 = vecPrib[i] + block1[k1];
                   k1++;
                   ochBlockRem_2 = 0;
                 }
                 else {
                   if (blockRem_3 <= vecPrib[i]) {
                     blockRem_3 = vecPrib[i] + block1[k1];
                     k1++;
                     ochBlockRem_3 = 0;
                   }
                   else {
                     if (blockRem_4 <= vecPrib[i]) {
                       blockRem_4 = vecPrib[i] + block1[k1];
                       k1++;
                       ochBlockRem_4 = 0;
                     }
                   }
                 }
               }
             }
             else {
               if ((blockRem_1 <= blockRem_2) && (blockRem_1 <= blockRem_3) && (blockRem_1 <= blockRem_4)) {
                 ochBlockRem_1++;
                 blockRem_1 += block1[k1];
                 k1++;
               }
               else {
                 if ((blockRem_2 < blockRem_1) && (blockRem_2 <= blockRem_3) && (blockRem_2 <= blockRem_4)) {
                   ochBlockRem_2++;
                   blockRem_2 += block1[k1];
                   k1++;
                 }
                 else {
                   if ((blockRem_3 < blockRem_1) && (blockRem_3 < blockRem_2) && (blockRem_3 <= blockRem_4)) {
                     ochBlockRem_3++;
                     blockRem_3 += block1[k1];
                     k1++;
                   }
                   else {
                     if ((blockRem_4 < blockRem_1) && (blockRem_4 < blockRem_2) && (blockRem_4 < blockRem_3)) {
                       ochBlockRem_4++;
                       blockRem_4 += block1[k1];
                       k1++;
                     }
                   }
                 }
               }
             }
             //  std::cout << blockRem_1 << " " << blockRem_2 << " " << blockRem_3 << " " << ochBlockRem_1 << " " << ochBlockRem_2 << " " << ochBlockRem_3 << " " << i << " \n";

             maxOchBlockRem_1 = std::max(ochBlockRem_1, maxOchBlockRem_1);
             maxOchBlockRem_2 = std::max(ochBlockRem_2, maxOchBlockRem_2);
             maxOchBlockRem_3 = std::max(ochBlockRem_3, maxOchBlockRem_3);
             maxOchBlockRem_4 = std::max(ochBlockRem_4, maxOchBlockRem_4);
           }

           if (vecBloc[i] == 2) {
             if ((blockRem_1 <= vecPrib[i]) || (blockRem_2 <= vecPrib[i]) || (blockRem_3 <= vecPrib[i]) || (blockRem_4 <= vecPrib[i])) {
               if (blockRem_1 <= vecPrib[i]) {
                 blockRem_1 = vecPrib[i] + block2[k2];
                 k2++;
                 ochBlockRem_1 = 0;
               }
               else {
                 if (blockRem_2 <= vecPrib[i]) {
                   blockRem_2 = vecPrib[i] + block2[k2];
                   k2++;
                   ochBlockRem_2 = 0;
                 }
                 else {
                   if (blockRem_3 <= vecPrib[i]) {
                     blockRem_3 = vecPrib[i] + block2[k2];
                     k2++;
                     ochBlockRem_3 = 0;
                   }
                   else {
                     if (blockRem_4 <= vecPrib[i]) {
                       blockRem_4 = vecPrib[i] + block2[k2];
                       k2++;
                       ochBlockRem_4 = 0;
                     }
                   }
                 }
               }
             }
             else {
               if ((blockRem_1 <= blockRem_2) && (blockRem_1 <= blockRem_3) && (blockRem_1 <= blockRem_4)) {
                 ochBlockRem_1++;
                 blockRem_1 += block2[k2];
                 k2++;
               }
               else {
                 if ((blockRem_2 < blockRem_1) && (blockRem_2 <= blockRem_3) && (blockRem_2 <= blockRem_4)) {
                   ochBlockRem_2++;
                   blockRem_2 += block2[k2];
                   k2++;
                 }
                 else {
                   if ((blockRem_3 < blockRem_1) && (blockRem_3 < blockRem_2) && (blockRem_3 <= blockRem_4)) {
                     ochBlockRem_3++;
                     blockRem_3 += block2[k2];
                     k2++;
                   }
                   else {
                     if ((blockRem_4 < blockRem_1) && (blockRem_4 < blockRem_2) && (blockRem_4 < blockRem_3)) {
                       ochBlockRem_4++;
                       blockRem_4 += block2[k2];
                       k2++;
                     }
                   }
                 }
               }
             }
             //  std::cout << blockRem_1 << " " << blockRem_2 << " " << blockRem_3 << " " << ochBlockRem_1 << " " << ochBlockRem_2 << " " << ochBlockRem_3 << " " << i << " \n";

             maxOchBlockRem_1 = std::max(ochBlockRem_1, maxOchBlockRem_1);
             maxOchBlockRem_2 = std::max(ochBlockRem_2, maxOchBlockRem_2);
             maxOchBlockRem_3 = std::max(ochBlockRem_3, maxOchBlockRem_3);
             maxOchBlockRem_4 = std::max(ochBlockRem_4, maxOchBlockRem_4);
           }


           if (vecBloc[i] == 3) {
             if ((blockRem_1 <= vecPrib[i]) || (blockRem_2 <= vecPrib[i]) || (blockRem_3 <= vecPrib[i]) || (blockRem_4 <= vecPrib[i])) {
               if (blockRem_1 <= vecPrib[i]) {
                 blockRem_1 = vecPrib[i] + block3[k3];
                 k3++;
                 ochBlockRem_1 = 0;
               }
               else {
                 if (blockRem_2 <= vecPrib[i]) {
                   blockRem_2 = vecPrib[i] + block3[k3];
                   k3++;
                   ochBlockRem_2 = 0;
                 }
                 else {
                   if (blockRem_3 <= vecPrib[i]) {
                     blockRem_3 = vecPrib[i] + block3[k3];
                     k3++;
                     ochBlockRem_3 = 0;
                   }
                   else {
                     if (blockRem_4 <= vecPrib[i]) {
                       blockRem_4 = vecPrib[i] + block3[k3];
                       k3++;
                       ochBlockRem_4 = 0;
                     }
                   }
                 }
               }
             }
             else {
               if ((blockRem_1 <= blockRem_2) && (blockRem_1 <= blockRem_3) && (blockRem_1 <= blockRem_4)) {
                 ochBlockRem_1++;
                 blockRem_1 += block3[k3];
                 k3++;
               }
               else {
                 if ((blockRem_2 < blockRem_1) && (blockRem_2 <= blockRem_3)&& (blockRem_2 <= blockRem_4)) {
                   ochBlockRem_2++;
                   blockRem_2 += block3[k3];
                   k3++;
                 }
                 else {
                   if ((blockRem_3 < blockRem_1) && (blockRem_3 < blockRem_2) && (blockRem_3 <= blockRem_4)) {
                     ochBlockRem_3++;
                     blockRem_3 += block3[k3];
                     k3++;
                   }
                   else {
                     if ((blockRem_4 < blockRem_1) && (blockRem_4 < blockRem_2) && (blockRem_4 < blockRem_3)) {
                       ochBlockRem_4++;
                       blockRem_4 += block3[k3];
                       k3++;
                     }
                   }
                 }
               }
             }
             // std::cout << blockRem_1 << " " << blockRem_2 << " " << blockRem_3 << " " << ochBlockRem_1 << " " << ochBlockRem_2 << " " << ochBlockRem_3 << " " << i << " \n";

             maxOchBlockRem_1 = std::max(ochBlockRem_1, maxOchBlockRem_1);
             maxOchBlockRem_2 = std::max(ochBlockRem_2, maxOchBlockRem_2);
             maxOchBlockRem_3 = std::max(ochBlockRem_3, maxOchBlockRem_3);
             maxOchBlockRem_4 = std::max(ochBlockRem_4, maxOchBlockRem_4);
           }

           if (vecBloc[i] == 4) {
             if ((blockTO_1 <= vecPrib[i]) || (blockTO_2 <= vecPrib[i])) {
               if (blockTO_1 <= vecPrib[i]) {
                 blockTO_1 = vecPrib[i] + block0[k0];
                 vecPrib[i] += block0[k0];
                 k0++;
                 ochBlockTO_1 = 0;
               }
               else {
                 if (blockTO_2 < vecPrib[i]) {
                   blockTO_2 = vecPrib[i] + block0[k0];
                   vecPrib[i] += block0[k0];
                   k0++;
                   ochBlockTO_2 = 0;
                 }
               }
             }
             else {
               if (blockTO_1 <= blockTO_2) {
                 ochBlockTO_1++;
                 blockTO_1 += block0[k0];
                 vecPrib[i] = blockTO_1;
                 k0++;
               }
               else {
                 ochBlockTO_2++;
                 blockTO_2 += block0[k0];
                 vecPrib[i] = blockTO_2;
                 k0++;
               }
             }
             //std::cout << blockTO_1 << " " << blockTO_2 << " " << ochBlockTO_1 << " " << ochBlockTO_2 << " " << i << " \n";
             //std::cout << blockRem_1 << " " << blockRem_2 << " " << blockRem_3 << " " << ochBlockRem_1 << " " << ochBlockRem_2 << " " << ochBlockRem_3 << " " << i << " \n";

             maxOchBlockTO_1 = std::max(ochBlockTO_1, maxOchBlockTO_1);
             maxOchBlockTO_2 = std::max(ochBlockTO_2, maxOchBlockTO_2);
             //std::cout << blockTO_1 << " " << blockTO_2 << " " << ochBlockTO_1 << " " << ochBlockTO_2 << " " << i << " \n";
             vecBloc[i] = 2;
             int a = i, b;
             double tmp;
             //  std::cout << blockTO_1 << " " << blockTO_2 << " " << ochBlockTO_1 << " " << ochBlockTO_2 << " " << i << " \n";
             if (a < kol - 2) {
               while ((vecPrib[a] > vecPrib[a + 1]) && (a < kol - 2)) {
                 tmp = vecPrib[a];
                 vecPrib[a] = vecPrib[a + 1];
                 vecPrib[a + 1] = tmp;
                 b = vecBloc[a];
                 vecBloc[a] = vecBloc[a + 1];
                 vecBloc[a + 1] = b;
                 //std::cout << a << " ";
                 a++;
                 //std::cout << a << " ";
               }
             }
             // std::cout << blockTO_1 << " " << blockTO_2 << " " << ochBlockTO_1 << " " << ochBlockTO_2 << " " << i << " \n";
             i--;

           }
         }

    }
    new_label = QString::number(maxOchBlockTO_1, 'g', 15);
    ui->label_och0->setText(new_label);
    new_label = QString::number(maxOchBlockTO_2, 'g', 15);
    ui->label_och1->setText(new_label);
    new_label = QString::number(maxOchBlockRem_1, 'g', 15);
    ui->label_och2->setText(new_label);
    new_label = QString::number(maxOchBlockRem_2, 'g', 15);
    ui->label_och3->setText(new_label);
    new_label = QString::number(maxOchBlockRem_3, 'g', 15);
    ui->label_och4->setText(new_label);
    if(remBlock==4){
        new_label = QString::number(maxOchBlockRem_4, 'g', 15);
        ui->label_och5->setText(new_label);
    }else{
        new_label = QString::number(-0, 'g', 15);
        ui->label_och5->setText(new_label);
    }

//------------Гистограмма количества поступивших машин--------------------------
    QCustomPlot *customPlot1 = ui->customPlot;

    QCPBars *fossil1 = new QCPBars(customPlot1->xAxis, customPlot1->yAxis);

    customPlot1->addPlottable(fossil1);
    // Установки цвета:
    QPen pen1;
    pen1.setWidthF(1.5);//Толщина контура столбца
    fossil1->setName(QString::fromUtf8("Гистограмма")); // Легенда
    pen1.setColor(QColor(50, 50, 100));// Цвет контура столбца
    fossil1->setPen(pen1);
    // Цвет самого столбца, четвертый параметр - прозрачность
    fossil1->setBrush(QColor(50, 50, 250, 150));

    // Установки значений оси X:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4;
    labels << "ТО" << "Простой" << "Средний" << "Сложный";
    customPlot1->xAxis->setAutoTicks(false);
    customPlot1->xAxis->setAutoTickLabels(false);
    customPlot1->xAxis->setTickVector(ticks);
    customPlot1->xAxis->setTickVectorLabels(labels);
    customPlot1->xAxis->setSubTickCount(0);
    customPlot1->xAxis->setTickLength(0, 4);
    customPlot1->xAxis->grid()->setVisible(true);
    customPlot1->xAxis->setRange(0.5, 4.5);

    int max_r = std::max(j,r1);
    max_r = std::max(max_r,r2);
    max_r = std::max(max_r,r3);
    max_r +=5;


    // Установки значений оси Y:
    customPlot1->yAxis->setRange(0, max_r);
    customPlot1->yAxis->setPadding(5);
    //customPlot->yAxis->setLabel(QString::fromUtf8("Значения элементов"));
    customPlot1->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    customPlot1->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    customPlot1->yAxis->grid()->setSubGridPen(gridPen);


    // Данные:
    QVector<double> fossilData1;
    fossilData1  << j
                << r1
                << r2
                << r3;

    fossil1->setData(ticks, fossilData1);

    customPlot1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    customPlot1->replot();

    // Сброс всех установок графика:
    customPlot1->removePlottable(fossil1);

//------------Гистограмма среднего времени обслуживания машин--------------------------
    QCustomPlot *customPlot2 = ui->widget_2;

    QCPBars *fossil2 = new QCPBars(customPlot2->xAxis, customPlot2->yAxis);

    customPlot2->addPlottable(fossil2);
    // Установки цвета:
    QPen pen2;
    pen2.setWidthF(1.5);//Толщина контура столбца
    fossil2->setName(QString::fromUtf8("Гистограмма")); // Легенда
    pen2.setColor(QColor(50, 50, 100));// Цвет контура столбца
    fossil2->setPen(pen2);
    // Цвет самого столбца, четвертый параметр - прозрачность
    fossil2->setBrush(QColor(50, 50, 250, 150));

    // Установки значений оси X:
   // QVector<double> ticks;
   // QVector<QString> labels;
   // ticks << 1 << 2 << 3 << 4;
   // labels << "ТО" << "Простой" << "Средний" << "Сложный";
    customPlot2->xAxis->setAutoTicks(false);
    customPlot2->xAxis->setAutoTickLabels(false);
    customPlot2->xAxis->setTickVector(ticks);
    customPlot2->xAxis->setTickVectorLabels(labels);
    customPlot2->xAxis->setSubTickCount(0);
    customPlot2->xAxis->setTickLength(0, 4);
    customPlot2->xAxis->grid()->setVisible(true);
    customPlot2->xAxis->setRange(0.5, 4.5);

    double max_t = std::max(t_to,t_pr);
    max_t = std::max(max_t,t_sr);
    max_t = std::max(max_t,t_sl);
    int max_T = (int)max_t;
    max_T +=10;


    // Установки значений оси Y:
    customPlot2->yAxis->setRange(0, max_T);
    customPlot2->yAxis->setPadding(5);
    //customPlot->yAxis->setLabel(QString::fromUtf8("Значения элементов"));
    customPlot2->yAxis->grid()->setSubGridVisible(true);
   // QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    customPlot2->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    customPlot2->yAxis->grid()->setSubGridPen(gridPen);


    // Данные:
    QVector<double> fossilData2;
    fossilData2  << t_to
                << t_pr
                << t_sr
                << t_sl;

    fossil2->setData(ticks, fossilData2);

    customPlot2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    customPlot2->replot();

    // Сброс всех установок графика:
    customPlot2->removePlottable(fossil2);

//----------------Гистограмма выручки каждого блока---------------------------------------------------
     QCustomPlot *customPlot = ui->widget_3;

     QCPBars *fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);

     customPlot->addPlottable(fossil);
     // Установки цвета:
     QPen pen;
     pen.setWidthF(1.5);//Толщина контура столбца
     fossil->setName(QString::fromUtf8("Гистограмма")); // Легенда
     pen.setColor(QColor(50, 50, 100));// Цвет контура столбца
     fossil->setPen(pen);
     // Цвет самого столбца, четвертый параметр - прозрачность
     fossil->setBrush(QColor(50, 50, 250, 150));

     // Установки значений оси X:
     //QVector<double> ticks;
    // QVector<QString> labels;
    // ticks << 1 << 2 << 3 << 4;
    //labels << "ТО" << "Простой" << "Средний" << "Сложный";
     customPlot->xAxis->setAutoTicks(false);
     customPlot->xAxis->setAutoTickLabels(false);
     customPlot->xAxis->setTickVector(ticks);
     customPlot->xAxis->setTickVectorLabels(labels);
     customPlot->xAxis->setSubTickCount(0);
     customPlot->xAxis->setTickLength(0, 4);
     customPlot->xAxis->grid()->setVisible(true);
     customPlot->xAxis->setRange(0.5, 4.5);

     double max_s = std::max(s_to,s_pr);
     max_s = std::max(max_s,s_sr);
     max_s = std::max(max_s,s_sl);
     int max_S = (int)max_s;
     max_S +=100;


     // Установки значений оси Y:
     customPlot->yAxis->setRange(0, max_S);
     customPlot->yAxis->setPadding(5);
     //customPlot->yAxis->setLabel(QString::fromUtf8("Значения элементов"));
     customPlot->yAxis->grid()->setSubGridVisible(true);
    // QPen gridPen;
    // gridPen.setStyle(Qt::SolidLine);
   //  gridPen.setColor(QColor(0, 0, 0, 25));
   //  customPlot->yAxis->grid()->setPen(gridPen);
   //  gridPen.setStyle(Qt::DotLine);
   //  customPlot->yAxis->grid()->setSubGridPen(gridPen);


     // Данные:
     QVector<double> fossilData;
     fossilData  << s_to
                 << s_pr
                 << s_sr
                 << s_sl;

     fossil->setData(ticks, fossilData);

     customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
     customPlot->replot();

     // Сброс всех установок графика:
     customPlot->removePlottable(fossil);

//----------------Гистограмма jxthtltq ,jrcjd ---------------------------------------------------
          QCustomPlot *customPlot4 = ui->widget_4;

          QCPBars *fossil4 = new QCPBars(customPlot4->xAxis, customPlot4->yAxis);

          customPlot4->addPlottable(fossil4);
          // Установки цвета:
          QPen pen4;
          pen4.setWidthF(1.5);//Толщина контура столбца
          fossil4->setName(QString::fromUtf8("Гистограмма")); // Легенда
          pen4.setColor(QColor(50, 50, 100));// Цвет контура столбца
          fossil4->setPen(pen4);
          // Цвет самого столбца, четвертый параметр - прозрачность
          fossil4->setBrush(QColor(50, 50, 250, 150));

          // Установки значений оси X:
          QVector<double> ticks4;
          QVector<QString> labels4;
          ticks4 << 1 << 2 << 3 << 4 << 5 << 6;
         labels4 << "ТО1" << "ТО2" << "Рем1" << "Рем2" << "Рем3" << "Рем4";
          customPlot4->xAxis->setAutoTicks(false);
          customPlot4->xAxis->setAutoTickLabels(false);
          customPlot4->xAxis->setTickVector(ticks4);
          customPlot4->xAxis->setTickVectorLabels(labels4);
          customPlot4->xAxis->setSubTickCount(0);
          customPlot4->xAxis->setTickLength(0, 4);
          customPlot4->xAxis->grid()->setVisible(true);
          customPlot4->xAxis->setRange(0, 7);

          int max_s4 = std::max(maxOchBlockTO_1,maxOchBlockTO_2);
          max_s4 = std::max(max_s4,maxOchBlockRem_1);
          max_s4 = std::max(max_s4,maxOchBlockRem_2);
          max_s4 = std::max(max_s4,maxOchBlockRem_3);
          max_s4 = std::max(max_s4,maxOchBlockRem_4);
          int max_S4 = (int)max_s4;
          max_S4 +=2;


          // Установки значений оси Y:
          customPlot4->yAxis->setRange(0, max_S4);
          customPlot4->yAxis->setPadding(6);
          //customPlot->yAxis->setLabel(QString::fromUtf8("Значения элементов"));
          customPlot4->yAxis->grid()->setSubGridVisible(true);
         // QPen gridPen;
         // gridPen.setStyle(Qt::SolidLine);
        //  gridPen.setColor(QColor(0, 0, 0, 25));
        //  customPlot->yAxis->grid()->setPen(gridPen);
        //  gridPen.setStyle(Qt::DotLine);
        //  customPlot->yAxis->grid()->setSubGridPen(gridPen);


          // Данные:
          QVector<double> fossilData4;
          fossilData4  << maxOchBlockTO_1
                      << maxOchBlockTO_2
                      << maxOchBlockRem_1
                      << maxOchBlockRem_2
                      << maxOchBlockRem_3
                      << maxOchBlockRem_4;

          fossil4->setData(ticks4, fossilData4);

          customPlot4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
          customPlot4->replot();

          // Сброс всех установок графика:
          customPlot4->removePlottable(fossil4);

}
