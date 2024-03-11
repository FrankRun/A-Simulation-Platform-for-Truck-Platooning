#include"Control.h"

Control::Control()
{

}
Control::Control(const int LANE_OFFSET,const int POSITION_OFFSET,const int Step_total, double innerplatoonheadway, double safedistance,const double ACC_prmts[]):
    LANE_OFFSET(LANE_OFFSET),POSITION_OFFSET(POSITION_OFFSET),Step_total(Step_total), innerplatoonheadway(innerplatoonheadway),safedistance(safedistance)
{
    this->ACC_prmts[0] = ACC_prmts[0];
    this->ACC_prmts[1] = ACC_prmts[1];
    this->ACC_prmts[2] = ACC_prmts[2];
    this->ACC_prmts[3] = ACC_prmts[3];
    this->ACC_prmts[4] = ACC_prmts[4];
    this->followcolor = 4294679300;
    this->leadingcolor=4294966784;
    this->originalcolor = -16777216;
    this->timesOfTransition = 20;
}
Control::~Control()
{

}

bool Control::latcontrol(double Simulation_step_time, double Lat_position_error0, double Wheel_angle0, double Yaw_angle_error0, int Step_total,
    MatrixXd k0, MatrixXd Lat_position_tar, MatrixXd s, MatrixXd lat_slope, MatrixXd state_vector_lonspeed, MatrixXd Head_angle_tar, MatrixXd& State_vector,int numinplatoon)
{
    int Iter_times_max; Iter_times_max = 100;
    double Beta_Lat_position_error; 
	if(numinplatoon ==1)
	{Beta_Lat_position_error = 5;}
	else
	{Beta_Lat_position_error = 25;}
    double Beta_Yaw_angle_error = 250;
    double Beta_Wheel_angle = 0;
    double Beta_Wheel_angle_com = 2000;
    double Wheelbase_f = 3.042;//1.265;
    double Wheelbase_r = 4.028;//1.675;
    double Wheel_angle_delay = 0.5;
    double k_istep;
    double lat_slope_istep;
    double Wheel_angle_max = 0.3;
    double Wheel_angle_change_rate_max = 0.3;

    Matrix<double, 4, 4>  Beta; Beta.setZero();
    Beta(0, 0) = Beta_Lat_position_error;  
    Beta(1, 1) = Beta_Yaw_angle_error; 
    Beta(2, 2) = Beta_Wheel_angle;
    Beta(3, 3) = Beta_Wheel_angle_com; 
    MatrixXd k = k0;
    MatrixXd Control_vector_new(1, Step_total); Control_vector_new.setZero();
    MatrixXd Control_vector(1, Step_total); Control_vector.setZero();
    MatrixXd Lat_position(1, Step_total + 1); Lat_position.setZero();
    MatrixXd Head_angle(1, Step_total + 1); Head_angle.setZero();
    MatrixXd Wheel_angle(1, Step_total + 1); Wheel_angle.setZero();
    MatrixXd Wheel_angle_commanded(1, Step_total);
    State_vector.setZero();

    for (int Iter_times = 0; Iter_times < Iter_times_max; Iter_times++)
    {
        Lat_position(0) = Lat_position_error0;
        Head_angle(0) = Yaw_angle_error0;
        Wheel_angle(0) = Wheel_angle0;
        Wheel_angle_commanded = Control_vector_new;

        for (int i = 0; i < Step_total; i++)
        {
            Lat_position(i + 1) = Lat_position(i) + Head_angle(i) * s(i) * cos(lat_slope(i));
            Head_angle(i + 1) = Head_angle(i) + (Wheel_angle(i) / (Wheelbase_f + Wheelbase_r) - k(i)) * s(i);
            Wheel_angle(i + 1) = Wheel_angle(i) - Wheel_angle(i) / Wheel_angle_delay * s(i) / state_vector_lonspeed(i) + Wheel_angle_commanded(i) / Wheel_angle_delay * s(i) / state_vector_lonspeed(i);
        }
        State_vector.row(0) = Lat_position; State_vector.row(1) = Head_angle; State_vector.row(2) = Wheel_angle;  
        Control_vector = Wheel_angle_commanded;

        double Lat_position_istep = Lat_position(Step_total);
        double Head_angle_istep = Head_angle(Step_total);
        double Speed_istep = state_vector_lonspeed(Step_total);
        double Wheel_angle_istep = Wheel_angle(Step_total);
        double Wheel_angle_desired_istep = Wheel_angle_commanded(Step_total - 1);
        double Lat_position_tar_istep = Lat_position_tar(Step_total);
        double Head_angle_tar_istep = Head_angle_tar(Step_total);
       
        MatrixXd QQ = 2 * Beta * s(Step_total - 1);
        MatrixXd Q = QQ.block(0, 0, QQ.rows() - 1, QQ.cols() - 1);

        VectorXd z(3); z << Lat_position_istep, Head_angle_istep, Wheel_angle_istep;
        VectorXd u(1); u << Wheel_angle_desired_istep;
        VectorXd D(3); D << 2 * Beta(0, 0) * (Lat_position_istep - Lat_position_tar_istep), 2 * Beta(1, 1) * (Head_angle_istep - Head_angle_tar_istep), 2 * Beta(2, 2) * Wheel_angle_istep;

        D = D * s(Step_total - 1) - Q * z;
        VectorXd R(1);
        R(0) = 2 * Beta(Beta.rows() - 1, Beta.cols() - 1) * s(Step_total - 1);
        VectorXd F = 2 * Beta(Beta.rows() - 1, Beta.cols() - 1) * u * s(Step_total - 1) - R * u;
        VectorXd J(1);
        J(0) = Beta(0, 0) * pow(Lat_position_istep - Lat_position_tar_istep, 2) + Beta(1, 1) * pow(Head_angle_istep - Head_angle_tar_istep, 2) + Beta(2, 2) * pow(Wheel_angle_istep, 2) + Beta(3, 3) * pow(Wheel_angle_desired_istep - Wheel_angle_istep, 2);
        VectorXd E = J - (z.transpose() * D + z.transpose() * Q * z / 2) - (u.transpose() * F + u.transpose() * R * u / 2);

        MatrixXd QkP1 = Q; VectorXd DkP1 = D; VectorXd EkP1 = E;

        Matrix<MatrixXd, -1, 1> GM(Step_total);
        Matrix<MatrixXd, -1, 1> HM(Step_total);
        for (int a = 0; a < Step_total; a++)
        {
            GM(a).setZero(1, 3);
            HM(a).setZero(1, 1);
        }
        for (int i = Step_total - 1; i > -1; i--)
        {
            Lat_position_istep = Lat_position(i);
            Head_angle_istep = Head_angle(i);
            Head_angle_tar_istep = Head_angle_tar(i);
            Speed_istep = state_vector_lonspeed(i);
            Wheel_angle_istep = Wheel_angle(i);
            Wheel_angle_desired_istep = Wheel_angle_commanded(i);
            Lat_position_tar_istep = Lat_position_tar(i);
            k_istep = k(i);
            lat_slope_istep = lat_slope(i);

            MatrixXd A(3, 3); MatrixXd B(3, 1); MatrixXd C(3, 1);
            A << 0, cos(lat_slope_istep), 0,
                0, 0, 1 / (Wheelbase_f + Wheelbase_r),
                0, 0, -1 / Wheel_angle_delay / Speed_istep;
            A = A * s(i) + MatrixXd::Identity(3, 3);
            B << 0, 0, 1 / Wheel_angle_delay / Speed_istep;
            B = B * s(i);
            C << 0, -k_istep * s(i), 0;

            QQ = 2 * Beta * s(i);
            Q = QQ.block(0, 0, QQ.rows() - 1, QQ.cols() - 1);

            z << Lat_position_istep, Head_angle_istep, Wheel_angle_istep;
            u << Wheel_angle_desired_istep;

            D << 2 * Beta(0, 0) * (Lat_position_istep - Lat_position_tar_istep), 2 * Beta(1, 1) * (Head_angle_istep - Head_angle_tar_istep), 2 * Beta(2, 2) * Wheel_angle_istep;
            D = D * s(i) - Q * z;

            R(0) = 2 * Beta(Beta.rows() - 1, Beta.cols() - 1) * s(i);
            F = 2 * Beta(Beta.rows() - 1, Beta.cols() - 1) * u * s(i) - R * u;

            J(0) = Beta(0, 0) * pow(Lat_position_istep - Lat_position_tar_istep, 2) + Beta(1, 1) * pow(Head_angle_istep - Head_angle_tar_istep, 2) + Beta(2, 2) * pow(Wheel_angle_istep, 2) + Beta(3, 3) * pow(Wheel_angle_desired_istep - Wheel_angle_istep, 2);
            E = J - (z.transpose() * D + z.transpose() * Q * z / 2) - (u.transpose() * F + u.transpose() * R * u / 2);

            MatrixXd Ak = A;
            MatrixXd Bk = B;
            MatrixXd Rk = R;
            MatrixXd Fk = F;
            MatrixXd Ck = C;
            MatrixXd Pk = (Rk + Bk.transpose() * QkP1 * Bk).inverse();
            MatrixXd Gk = -Pk * Bk.transpose() * QkP1 * Ak;
            MatrixXd Hk = -Pk * (Bk.transpose() * (DkP1 + QkP1 * Ck) + Fk);
            MatrixXd Sk = Ak + Bk * Gk;
            MatrixXd Tk = Bk * Hk + Ck;
            GM(i) = Gk;
            HM(i) = Hk;

            MatrixXd Qk = Gk.transpose() * Rk * Gk + Sk.transpose() * QkP1 * Sk + Q;
            MatrixXd Dk = Gk.transpose() * Rk * Hk + Sk.transpose() * QkP1 * Tk + Sk.transpose() * DkP1 + Gk.transpose() * Fk + D;
            MatrixXd EK = Hk.transpose() * Rk * Hk / 2 + Tk.transpose() * QkP1 * Tk / 2 + Hk.transpose() * Fk + Tk.transpose() * DkP1 + EkP1 + E;
            QkP1 = Qk; DkP1 = Dk; EkP1 = EK;
        }

        for (int i = 0; i < Step_total; i++)
        {
            Head_angle_istep = State_vector(1, i);
            k_istep = k(i);
            lat_slope_istep = lat_slope(i);
            Speed_istep = state_vector_lonspeed(i);
            Control_vector_new.col(i) = GM(i) * State_vector.col(i) + HM(i);
            MatrixXd A(3, 3); MatrixXd B(3, 1); MatrixXd C(3, 1);
            A << 0, cos(lat_slope_istep), 0,
                0, 0, 1 / (Wheelbase_f + Wheelbase_r),
                0, 0, -1 / Wheel_angle_delay / Speed_istep;
            A = A * s(i) + MatrixXd::Identity(3, 3);
            B << 0, 0, 1 / Wheel_angle_delay / Speed_istep;
            B = B * s(i);
            C << 0, -k_istep * s(i), 0;
            MatrixXd Ak = A; MatrixXd Bk = B; MatrixXd Ck = C;
            if (Control_vector_new(0, i) > Wheel_angle_max)
            {
                Control_vector_new(0, i) = Wheel_angle_max;
            }
            if (Control_vector_new(0, i) < -Wheel_angle_max)
            {
                Control_vector_new(0, i) = -Wheel_angle_max;
            }
            State_vector.col(i + 1) = Ak * State_vector.col(i) + Bk * Control_vector_new.col(i) + Ck;
        }
        int stp = 1;
        for (int i = 0; i < Step_total; i++)
        {
            if (abs(Control_vector(0, i) - Control_vector_new(0, i)) > 0.001)
            {
                stp = 0;
            }
        }
        Control_vector = Control_vector_new;
        if (stp)
        {
            break;
        }
    }
    return true;
}

double Control::loncontrol(double dis, double v_local, double a0, double v_leading, double hi, double safedis, double af, double timestep, int numinplatoon)
{
    double Ts = timestep;
    double Ta = 0.8;
    double amax = 2;
    double amin = -4;
    Vector2d X0(dis - hi * v_local - safedis, v_leading - v_local - hi * a0); //state
    double C1 = (af + (hi - Ta) * (v_leading - v_local) / (Ta * hi)) * Ts; 
    double u = 0;
    if (innerplatoonheadway ==0.6)
    {
        
        switch (numinplatoon)
        {
        case 2:
            u = 0.113878145419722 * X0(0) + 1.15982073781317 * X0(1) + 9.70654244754223 * C1;
            break;
        case 3:
            u = 0.140042502961564 * X0(0) + 0.543799194900452 * X0(1) + 4.01221632256775 * C1;
            break;
        case 4:
            u = 0.155686605220791 * X0(0) + 0.501785368158062 * X0(1) + 2.96015819832163 * C1;
            break;
        case 5:
            u = 0.164156322049522 * X0(0) + 0.495901635803280 * X0(1) + 2.41575117870537 * C1;
            break;
        case 6:
            u = 0.168064182639862 * X0(0) + 0.494092898595283 * X0(1) + 2.05126741709763 * C1;
            break;
        case 7:
            u = 0.169195695685325 * X0(0) + 0.491478516764792 * X0(1) + 1.78461312474684 * C1;
            break;
        case 8:
            u = 0.168628115711673 * X0(0) + 0.487356365140407 * X0(1) + 1.58005503882427 * C1;
            break;
        case 9:
            u = 0.167003470530797 * X0(0) + 0.481865741870391 * X0(1) + 1.41786872424561 * C1;
            break;
        case 10:
            u = 0.164712208081140 * X0(0) + 0.475294549286673 * X0(1) + 1.28598001217840 * C1;
            break;
        default:
            break;
        }
    }
    else if (innerplatoonheadway == 0.8)
    {
        
        switch (numinplatoon)
        {
        case 2:
            u = 0.124431191112663 * X0(0) + 0.725881574254857 * X0(1) + 6.13239386887000 * C1;
            break;
        case 3:
            u = 0.151411363545339 * X0(0) + 0.507906805176069 * X0(1) + 3.21814727839443 * C1;
            break;
        case 4:
            u = 0.164156322049522 * X0(0) + 0.495901635803280 * X0(1) + 2.41575117870537 * C1;
            break;
        case 5:
            u = 0.168684999037417 * X0(0) + 0.493378440702542 * X0(1) + 1.95376508842993 * C1;
            break;
        case 6:
            u = 0.168959928501143 * X0(0) + 0.488895301213740 * X0(1) + 1.64276411580502 * C1;
            break;
        case 7:
            u = 0.167003470530797 * X0(0) + 0.481865741870392 * X0(1) + 1.41786872424562 * C1;
            break;
        case 8:
            u = 0.163845515344942 * X0(0) + 0.472912806856541 * X0(1) + 1.24731000041166 * C1;
            break;
        case 9:
            u = 0.160036700017737 * X0(0) + 0.462666991913675 * X0(1) + 1.11335456837432 * C1;
            break;
        case 10:
            u = 0.155888210290918 * X0(0) + 0.451614205480467 * X0(1) + 1.00528776908893 * C1;
            break;
        default:
            break;
        }
    }
    else if (innerplatoonheadway ==1.0)
    {
        
        switch (numinplatoon)
        {
        case 2:
            u = 0.132798403451658 * X0(0) + 0.595798364229995 * X0(1) + 4.74120018039657 * C1;
            break;
        case 3:
            u = 0.159164341915566 * X0(0) + 0.498582948374990 * X0(1) + 2.74899808075042 * C1;
            break;
        case 4:
            u = 0.168064182639862 * X0(0) + 0.494092898595283 * X0(1) + 2.05126741709763 * C1;
            break;
        case 5:
            u = 0.168959928501143 * X0(0) + 0.488895301213740 * X0(1) + 1.64276411580502 * C1;
            break;
        case 6:
            u = 0.166299414927351 * X0(0) + 0.479781002030653 * X0(1) + 1.37099289981910 * C1;
            break;
        case 7:
            u = 0.161999116929195 * X0(0) + 0.467917670627249 * X0(1) + 1.17654288161858 * C1;
            break;
        case 8:
            u = 0.156945568176487 * X0(0) + 0.454431770082504 * X0(1) + 1.03030054584740 * C1;
            break;
        case 9:
            u = 0.151584621926358 * X0(0) + 0.440107917286364 * X0(1) + 0.916236093202432 * C1;
            break;
        case 10:
            u = 0.146155861127751 * X0(0) + 0.425465970800428 * X0(1) + 0.824758876201784 * C1;
            break;
        default:
            break;
        }
    }
    else if (innerplatoonheadway == 1.2)
    {
     
        switch (numinplatoon)
        {
        case 2:
            u = 0.140042502961564 * X0(0) + 0.543799194900452 * X0(1) + 4.01221632256775 * C1;
            break;
        case 3:
            u = 0.164156322049522 * X0(0) + 0.495901635803280 * X0(1) + 2.41575117870537 * C1;
            break;
        case 4:
            u = 0.169195695685325 * X0(0) + 0.491478516764792 * X0(1) + 1.78461312474684 * C1;
            break;
        case 5:
            u = 0.167003470530797 * X0(0) + 0.481865741870391 * X0(1) + 1.41786872424561 * C1;
            break;
        case 6:
            u = 0.161999116929195 * X0(0) + 0.467917670627249 * X0(1) + 1.17654288161858 * C1;
            break;
        case 7:
            u = 0.155888210290918 * X0(0) + 0.451614205480467 * X0(1) + 1.00528776908893 * C1;
            break;
        case 8:
            u = 0.149412039158439 * X0(0) + 0.434266971756133 * X0(1) + 0.877334736577669 * C1;
            break;
        case 9:
            u = 0.142924697488344 * X0(0) + 0.416675427242494 * X0(1) + 0.778078079770044 * C1;
            break;
        case 10:
            u = 0.136604572181043 * X0(0) + 0.399320188468010 * X0(1) + 0.698838208683366 * C1;
            break;
        default:
            break;
        }
    }
    else if (innerplatoonheadway ==1.5)
    {
   
        switch (numinplatoon)
        {
        case 2:
            u = 0.148939828026443 * X0(0) + 0.512861778185117 * X0(1) + 3.37230397663089 * C1;
            break;
        case 3:
            u = 0.168064182639862 * X0(0) + 0.494092898595283 * X0(1) + 2.05126741709763 * C1;
            break;
        case 4:
            u = 0.167919162701955 * X0(0) + 0.484764662467728 * X0(1) + 1.49454719873568 * C1;
            break;
        case 5:
            u = 0.161999116929195 * X0(0) + 0.467917670627249 * X0(1) + 1.17654288161858 * C1;
            break;
        case 6:
            u = 0.154285271155410 * X0(0) + 0.447337021863567 * X0(1) + 0.969951349857044 * C1;
            break;
        case 7:
            u = 0.146155861127751 * X0(0) + 0.425465970800428 * X0(1) + 0.824758876201784 * C1;
            break;
        case 8:
            u = 0.138162954559619 * X0(0) + 0.403618746184872 * X0(1) + 0.717110892705031 * C1;
            break;
        case 9:
            u = 0.130542167603200 * X0(0) + 0.382485999624228 * X0(1) + 0.634121517469310 * C1;
            break;
        case 10:
            u = 0.123389822629048 * X0(0) + 0.362415866955271 * X0(1) + 0.568202163046568 * C1;
            break;
        default:
            break;
        }
    }
    else
    {
  
        switch (numinplatoon)
        {
        case 2:
            u = 0.124431191112663 * X0(0) + 0.725881574254857 * X0(1) + 6.13239386887000 * C1;
            break;
        case 3:
            u = 0.151411363545339 * X0(0) + 0.507906805176069 * X0(1) + 3.21814727839443 * C1;
            break;
        case 4:
            u = 0.164156322049522 * X0(0) + 0.495901635803280 * X0(1) + 2.41575117870537 * C1;
            break;
        case 5:
            u = 0.168684999037417 * X0(0) + 0.493378440702542 * X0(1) + 1.95376508842993 * C1;
            break;
        case 6:
            u = 0.168959928501143 * X0(0) + 0.488895301213740 * X0(1) + 1.64276411580502 * C1;
            break;
        case 7:
            u = 0.167003470530797 * X0(0) + 0.481865741870392 * X0(1) + 1.41786872424562 * C1;
            break;
        case 8:
            u = 0.163845515344942 * X0(0) + 0.472912806856541 * X0(1) + 1.24731000041166 * C1;
            break;
        case 9:
            u = 0.160036700017737 * X0(0) + 0.462666991913675 * X0(1) + 1.11335456837432 * C1;
            break;
        case 10:
            u = 0.155888210290918 * X0(0) + 0.451614205480467 * X0(1) + 1.00528776908893 * C1;
            break;
        default:
            break;
        }
    }

    if (u > amax)
    {
        u = amax;
    }
    else if (u < amin)
    {
        u = amin;
    }
    return u;
}

int Control::ACC_carFollowing(SimVehicle &currentVehicle, map<long, SimVehicle>& vehiclesInNet,SimVehicle adjacentVehicles[][5])
{
    long ID = currentVehicle.id;
    double ss = 0, spd_temp = 0, zs = 0, a_free = 0;
    double desiredSpeed = vehiclesInNet[ID].getDesiredSpeed();
    double Speed = vehiclesInNet[ID].getSpeed(); 
    double LeadingVeh_Dist;
    double LeadingVeh_Spd;
    LeadingVeh_Dist = currentVehicle.getHeadwayDistance() - adjacentVehicles[LANE_OFFSET][POSITION_OFFSET + 1].getLength();
    if (adjacentVehicles[LANE_OFFSET][POSITION_OFFSET + 1].id > 0)
    {
        LeadingVeh_Spd = adjacentVehicles[LANE_OFFSET][POSITION_OFFSET + 1].getSpeed();
    }
    else
    {
        LeadingVeh_Spd = desiredSpeed;
    }

    double decelerate_factor = 0.9;
    if (adjacentVehicles[LANE_OFFSET][POSITION_OFFSET + 1].id <= 0 &&
        adjacentVehicles[LANE_OFFSET - 1][POSITION_OFFSET + 1].id > 0 &&
        adjacentVehicles[LANE_OFFSET - 1][POSITION_OFFSET + 1].getActiveLaneChange() == 1) {
        
        LeadingVeh_Spd = adjacentVehicles[LANE_OFFSET - 1][POSITION_OFFSET + 1].getSpeed();
        LeadingVeh_Dist = decelerate_factor * (adjacentVehicles[LANE_OFFSET - 1][POSITION_OFFSET + 1].getHeadwayDistance() -
            adjacentVehicles[LANE_OFFSET - 1][POSITION_OFFSET + 1].getLength());
    }
    else if (adjacentVehicles[LANE_OFFSET][POSITION_OFFSET + 1].id > 0 &&
        adjacentVehicles[LANE_OFFSET - 1][POSITION_OFFSET + 1].id > 0 &&
        adjacentVehicles[LANE_OFFSET - 1][POSITION_OFFSET + 1].getActiveLaneChange() == 1 &&
        adjacentVehicles[LANE_OFFSET][POSITION_OFFSET + 1].getHeadwayDistance() >
        adjacentVehicles[LANE_OFFSET - 1][POSITION_OFFSET + 1].getHeadwayDistance()) {
        
        LeadingVeh_Spd = adjacentVehicles[LANE_OFFSET - 1][POSITION_OFFSET + 1].getSpeed();
        LeadingVeh_Dist = decelerate_factor * (adjacentVehicles[LANE_OFFSET - 1][POSITION_OFFSET + 1].getHeadwayDistance() -
            adjacentVehicles[LANE_OFFSET - 1][POSITION_OFFSET + 1].getLength());
    }

    if (adjacentVehicles[LANE_OFFSET][POSITION_OFFSET + 1].id <= 0 &&
        adjacentVehicles[LANE_OFFSET + 1][POSITION_OFFSET + 1].id > 0 &&
        adjacentVehicles[LANE_OFFSET + 1][POSITION_OFFSET + 1].getActiveLaneChange() == -1) {
        
        LeadingVeh_Spd = adjacentVehicles[LANE_OFFSET + 1][POSITION_OFFSET + 1].getSpeed();
        LeadingVeh_Dist = decelerate_factor * (adjacentVehicles[LANE_OFFSET + 1][POSITION_OFFSET + 1].getHeadwayDistance() -
            adjacentVehicles[LANE_OFFSET + 1][POSITION_OFFSET + 1].getLength());
    }
    else if (adjacentVehicles[LANE_OFFSET][POSITION_OFFSET + 1].id > 0 &&
        adjacentVehicles[LANE_OFFSET + 1][POSITION_OFFSET + 1].id > 0 &&
        adjacentVehicles[LANE_OFFSET + 1][POSITION_OFFSET + 1].getActiveLaneChange() == -1 &&
        adjacentVehicles[LANE_OFFSET][POSITION_OFFSET + 1].getHeadwayDistance() >
        adjacentVehicles[LANE_OFFSET + 1][POSITION_OFFSET + 1].getHeadwayDistance()) {
        
        LeadingVeh_Spd = adjacentVehicles[LANE_OFFSET + 1][POSITION_OFFSET + 1].getSpeed();
        LeadingVeh_Dist = decelerate_factor * (adjacentVehicles[LANE_OFFSET + 1][POSITION_OFFSET + 1].getHeadwayDistance() -
            adjacentVehicles[LANE_OFFSET + 1][POSITION_OFFSET + 1].getLength());
    }
    if (Speed >= 0) { 
        if (desiredSpeed < LeadingVeh_Spd) spd_temp = desiredSpeed;
        else spd_temp = LeadingVeh_Spd;
        ss = ACC_prmts[2] + max(0, (Speed * ACC_prmts[1] + (Speed * (Speed - spd_temp)) / (2 * sqrt(ACC_prmts[3] * ACC_prmts[4]))));
        
        if (LeadingVeh_Dist == 0)
        {
            LeadingVeh_Dist = 0.1;
        }
        zs = (ss / LeadingVeh_Dist);
        
		if(zs<0)
		{
			zs =0;
		}
        if (Speed <= desiredSpeed) {
            a_free = ACC_prmts[3] * (1 - pow(Speed / desiredSpeed, 4));
            if (zs >= 1) vehiclesInNet[ID].setDesiredAcceleration(ACC_prmts[3] * (1 - pow(zs, 2)));
            else
            {
                if (a_free ==0)
                {
                    vehiclesInNet[ID].setDesiredAcceleration(0);
                }
                else
                {
                    vehiclesInNet[ID].setDesiredAcceleration(a_free * (1 - pow(zs, 2 * ACC_prmts[3] / a_free)));
                }
            }
        }
        else {
            a_free = -ACC_prmts[4] * (1 - pow(desiredSpeed / Speed, ACC_prmts[3] * 4 / ACC_prmts[4]));
            if (zs >= 1) vehiclesInNet[ID].setDesiredAcceleration(a_free + ACC_prmts[3] * (1 - pow(zs, 2)));
            else vehiclesInNet[ID].setDesiredAcceleration(a_free);
        }
    }
    if (vehiclesInNet[ID].getDesiredAcceleration() > 2)
    {
        vehiclesInNet[ID].setDesiredAcceleration(2);
    }
    if (vehiclesInNet[ID].getDesiredAcceleration() < -4)
    {
        vehiclesInNet[ID].setDesiredAcceleration(-4);
    }
    return 1;
}
int Control::carFollowing(MatrixParameter* Mx,SimVehicle &currentVehicle,VDM & CurrentVDM, map<long, SimVehicle>& vehiclesInNet, map<int, Platoon>& platoons, map<long, VDM> &VDMInNet, SimVehicle adjacentVehicles[][5])
{
    try {
       
        long ID = currentVehicle.id;
        SimVehicle::PlatoonStates tmpState = (SimVehicle::PlatoonStates)vehiclesInNet[ID].getPlatoonState();
        double previousfrontdist = vehiclesInNet[ID].getPreviousHeadwayDistance();
        double expSpeed = vehiclesInNet[ID].getSpeed();
        switch (tmpState) {
        case SimVehicle::PlatoonStatePlatoonLeading:
        {

            vehiclesInNet[ID].setColor(leadingcolor);
            ACC_carFollowing(currentVehicle,vehiclesInNet,adjacentVehicles);

            if (vehiclesInNet[ID].intial_speed < 0)
            {
                vehiclesInNet[ID].VDMdisabledtime = 0;
                vehiclesInNet[ID].intial_speed = expSpeed;
                VDMInNet[ID].SetParameter(expSpeed);
                for (int i = 0; i < timesOfTransition; i++) {
                    VDMInNet[ID].OneStep(0);
                }
            }
            if (currentVehicle.getPlatoonState() == SimVehicle::PlatoonStateVehTypeIsNotForPlatooning|| 
                currentVehicle.getPlatoonState() == SimVehicle::PlatoonStatePlatoonFollowing)
            {
                vehiclesInNet[ID].VDMdisabledtime = 0;
                VDMInNet.erase(ID);
                VDMInNet[ID] = CurrentVDM;
                VDMInNet[ID].Initialize();
                vehiclesInNet[ID].intial_speed = expSpeed;
                VDMInNet[ID].SetParameter(expSpeed);
                for (int i = 0; i < timesOfTransition ; i++) {
                    VDMInNet[ID].OneStep(vehiclesInNet[ID].getDesiredAcceleration());
                }
                if (currentVehicle.getPlatoonState() == SimVehicle::PlatoonStateVehTypeIsNotForPlatooning)
                {
                    vehiclesInNet[ID].settimeIntoCACC(1);
                }
            }
            VDMInNet[ID].OneStep(vehiclesInNet[ID].getDesiredAcceleration());

            vehiclesInNet[ID].setDesiredAcceleration(VDMInNet[ID].OutPutacc());//acceleration after VDM
            return 1;
        }
        case SimVehicle::PlatoonStatePlatoonFollowing:
        {
            vehiclesInNet[ID].setColor(followcolor);
            if (platoons[vehiclesInNet[ID].platoonID].getFrontIDof(ID) > 0)
            {
                //----------------------- Conroller Method ----------------------------
                int NumInPlatoon = platoons[vehiclesInNet[ID].platoonID].getNumInPlatoon(ID);
                //MPC compute acceleration
                vehiclesInNet[ID].setDesiredAcceleration(loncontrol(abs(platoons[vehiclesInNet[ID].platoonID].getPositionInPlatoon(vehiclesInNet, ID)), vehiclesInNet[ID].speed, vehiclesInNet[ID].acceleration, 
                    vehiclesInNet[platoons[vehiclesInNet[ID].platoonID].leadVehicleID].speed, innerplatoonheadway * (NumInPlatoon - 1), 
                    safedistance * (NumInPlatoon - 1), vehiclesInNet[platoons[vehiclesInNet[ID].platoonID].leadVehicleID].acceleration, currentVehicle.timestep, NumInPlatoon));

                if (vehiclesInNet[ID].intial_speed < 0)
                {
                    vehiclesInNet[ID].VDMdisabledtime = 0;
                    vehiclesInNet[ID].intial_speed = expSpeed;
                    VDMInNet[ID].SetParameter(expSpeed);
                    for (int i = 0; i < timesOfTransition; i++) {
                        VDMInNet[ID].OneStep(0);
                    }
                }
                if (currentVehicle.getPlatoonState() == SimVehicle::PlatoonStateVehTypeIsNotForPlatooning||
                    currentVehicle.getPlatoonState() == SimVehicle::PlatoonStatePlatoonLeading)
                {
                    vehiclesInNet[ID].VDMdisabledtime = 0;
                    VDMInNet.erase(ID);
                    VDMInNet[ID] = CurrentVDM;
                    VDMInNet[ID].Initialize();
                    vehiclesInNet[ID].intial_speed = expSpeed;
                    VDMInNet[ID].SetParameter(expSpeed);
                    for (int i = 0; i < timesOfTransition ; i++) {
                        VDMInNet[ID].OneStep(vehiclesInNet[ID].getDesiredAcceleration());
                    }
                    if (currentVehicle.getPlatoonState() == SimVehicle::PlatoonStateVehTypeIsNotForPlatooning)
                    {
                        vehiclesInNet[ID].settimeIntoCACC(1);
                    }
                  
                }
                //excute the VDM
                VDMInNet[ID].OneStep(vehiclesInNet[ID].getDesiredAcceleration());

                vehiclesInNet[ID].setDesiredAcceleration(VDMInNet[ID].OutPutacc());
                if (previousfrontdist == 0)
                {
                    vehiclesInNet[ID].setDesiredSpeed(currentVehicle.getDesiredSpeed());
                }
            }
            return 1;
        }
        case SimVehicle::PlatoonStatePlatoonLeaving:
            ACC_carFollowing(currentVehicle, vehiclesInNet, adjacentVehicles);
            return 1;
        default:
            return 0;
        }
    }
    catch (...)
    {
        return 0;
    }
}
int Control::lanechangecontrol(MatrixParameter* Mx,SimVehicle &currentVehicle,map<long,SimVehicle> &vehiclesInNet, map<int, Platoon>& platoons)
{
    long ID = currentVehicle.id;
    double Yaw_angle_error0;
    double Lat_position_error0;
    long activelanechange = vehiclesInNet[ID].activeLaneChange;
    long reltargetlane = vehiclesInNet[ID].relativeTargetLane;

    vehiclesInNet[ID].setusesimplelanechange(0);
    vehiclesInNet[ID].setuseinternalmodel(0);
    vehiclesInNet[ID].setActiveLaneChange(0);
    vehiclesInNet[ID].setRelativeTargetLane(0);
    vehiclesInNet[ID].setDesiredLaneAngle(0);

    //leading truck lane-changing
    if (vehiclesInNet[ID].platoonID != 0 && platoons[vehiclesInNet[ID].platoonID].getNumInPlatoon(ID) == 1)  
    {
        if (vehiclesInNet[ID].lanechangestate == 1 && vehiclesInNet[ID].returnlanestate == 0)
        {
            platoons[vehiclesInNet[ID].platoonID].platoonlanechangestate = 1;
            Yaw_angle_error0 = vehiclesInNet[ID].laneAngle;
            Lat_position_error0 = (vehiclesInNet[ID].currentLane - 1) * vehiclesInNet[ID].lanewidth + vehiclesInNet[ID].lanewidth / 2 + vehiclesInNet[ID].lateralPosition;
            if (platoons[vehiclesInNet[ID].platoonID].size != 1)
            {
                if (vehiclesInNet[ID].MPCstep == 200)
                {
                    --vehiclesInNet[ID].MPCstep;
                }
                platoons[vehiclesInNet[ID].platoonID].Lead_Lat_position_tar(0, vehiclesInNet[ID].MPCstep) = Lat_position_error0;  
                platoons[vehiclesInNet[ID].platoonID].Lead_Head_angle(0, vehiclesInNet[ID].MPCstep) = Yaw_angle_error0;
            }
            latcontrol(currentVehicle.timestep, Lat_position_error0, vehiclesInNet[ID].wheelangle, Yaw_angle_error0, Step_total, Mx->k0, Mx->Lat_position_tar, Mx->s, Mx->lat_slope,
                Mx->state_vector_lonspeed, Mx->Head_angle_tar, Mx->State_vector, platoons[vehiclesInNet[ID].platoonID].getNumInPlatoon(ID));

            vehiclesInNet[ID].wheelangle = Mx->State_vector(2, 1) - 0;
            
            if ((activelanechange == -1 && Mx->State_vector(1, 1) > 0)||(reltargetlane==-1 && Mx->State_vector(1,1)>0))
            {
                Mx->State_vector(1, 1) = 0;
            }
            else if ((activelanechange == 1 && Mx->State_vector(1, 1) < 0)||(reltargetlane == 1&&Mx->State_vector(1,1)<0))
            {
                Mx->State_vector(1, 1) = 0;
            }

            if (vehiclesInNet[ID].currentLane == platoons[vehiclesInNet[ID].platoonID].targetlane) 
            {
                if (abs(vehiclesInNet[ID].lateralPosition) < 0.03 || vehiclesInNet[ID].MPCstep > 190) 
                {
                    vehiclesInNet[ID].lanechangestate = 0;
                    vehiclesInNet[ID].MPCstep = 0;
                    vehiclesInNet[ID].wheelangle = 0;
                    vehiclesInNet[ID].desiredLaneAngle = 0;

                    if (platoons[vehiclesInNet[ID].platoonID].lanechangejudgment(vehiclesInNet, platoons, vehiclesInNet[ID].platoonID))  //  platoon lane-changing completed judgment
                    {
                        platoons[vehiclesInNet[ID].platoonID].currentlane = vehiclesInNet[ID].currentLane;   
                        platoons[vehiclesInNet[ID].platoonID].platoonlanechangestate = 0;
                    }
                    return 1;
                }
                else
                {
                    vehiclesInNet[ID].desiredLaneAngle = Mx->State_vector(1, 1);
                }
            }
            else
            {
                if (abs(vehiclesInNet[ID].lateralPosition) > (vehiclesInNet[ID].lanewidth / 2 + vehiclesInNet[ID].width / 2)) 
                {
                    vehiclesInNet[ID].setActiveLaneChange(platoons[vehiclesInNet[ID].platoonID].turndirection);
                    vehiclesInNet[ID].setRelativeTargetLane(platoons[vehiclesInNet[ID].platoonID].turndirection);
                }
                vehiclesInNet[ID].desiredLaneAngle = Mx->State_vector(1, 1);
            }
            vehiclesInNet[ID].MPCstep++;
            return 1;
        }
        else if (vehiclesInNet[ID].returnlanestate == 1)  //lane-returning
        {
            platoons[vehiclesInNet[ID].platoonID].platoonlanechangestate = 1;
            if (vehiclesInNet[ID].currentLane != platoons[vehiclesInNet[ID].platoonID].targetlane) 
            {
                vehiclesInNet[ID].setActiveLaneChange(0);
                vehiclesInNet[ID].setRelativeTargetLane(0);
            }
            else if (vehiclesInNet[ID].currentLane == platoons[vehiclesInNet[ID].platoonID].targetlane) 
            {
                vehiclesInNet[ID].setActiveLaneChange((platoons[vehiclesInNet[ID].platoonID].currentlane - platoons[vehiclesInNet[ID].platoonID].targetlane) < 0 ? -1 : 1);
                vehiclesInNet[ID].setRelativeTargetLane((platoons[vehiclesInNet[ID].platoonID].currentlane - platoons[vehiclesInNet[ID].platoonID].targetlane) < 0 ? -1 : 1);
            }
            Yaw_angle_error0 = vehiclesInNet[ID].laneAngle;
            if ((platoons[vehiclesInNet[ID].platoonID].currentlane - platoons[vehiclesInNet[ID].platoonID].targetlane) < 0 && vehiclesInNet[ID].laneAngle > 0)
            {
                Yaw_angle_error0 = 0;
            }
            else if ((platoons[vehiclesInNet[ID].platoonID].currentlane - platoons[vehiclesInNet[ID].platoonID].targetlane) > 0 && vehiclesInNet[ID].laneAngle < 0)
            {
                Yaw_angle_error0 = 0;
            }
            Lat_position_error0 = (vehiclesInNet[ID].currentLane - 1) * vehiclesInNet[ID].lanewidth + vehiclesInNet[ID].lanewidth / 2 + vehiclesInNet[ID].lateralPosition;
            latcontrol(currentVehicle.timestep, Lat_position_error0, vehiclesInNet[ID].wheelangle, Yaw_angle_error0, Step_total, Mx->k0, Mx->Lat_position_tar, Mx->s, Mx->lat_slope,
                Mx->state_vector_lonspeed, Mx->Head_angle_tar, Mx->State_vector, platoons[vehiclesInNet[ID].platoonID].getNumInPlatoon(ID));

            vehiclesInNet[ID].wheelangle = Mx->State_vector(2, 1) - 0;
            if ((activelanechange == 1 && Mx->State_vector(1, 1) < 0) || (vehiclesInNet[ID].activeLaneChange == 1 && Mx->State_vector(1, 1) < 0)||(reltargetlane == 1 && Mx->State_vector(1, 1) < 0))
            {
                Mx->State_vector(1, 1) = 0;
            }
            else if ((activelanechange == -1 && Mx->State_vector(1, 1) > 0) || (vehiclesInNet[ID].activeLaneChange == -1 && Mx->State_vector(1, 1) > 0)||(reltargetlane == -1&& Mx->State_vector(1, 1) > 0))
            {

                Mx->State_vector(1, 1) = 0;
            }
            vehiclesInNet[ID].desiredLaneAngle = Mx->State_vector(1, 1);

            if (abs(vehiclesInNet[ID].lateralPosition) < 0.03 && vehiclesInNet[ID].currentLane != platoons[vehiclesInNet[ID].platoonID].targetlane) 
            {
                vehiclesInNet[ID].lanechangestate = 0;
                vehiclesInNet[ID].returnlanestate = 0;
                vehiclesInNet[ID].MPCstep = 0;
                vehiclesInNet[ID].wheelangle = 0;
                vehiclesInNet[ID].desiredLaneAngle = 0;

                if (platoons[vehiclesInNet[ID].platoonID].lanechangereturnjudgment(vehiclesInNet, platoons, vehiclesInNet[ID].platoonID))
                {
                    platoons[vehiclesInNet[ID].platoonID].platoonlanechangestate = 0;
                }

                return 1;
            }
            return 1;
        }
    }
    else if (vehiclesInNet[ID].platoonID != 0 && platoons[vehiclesInNet[ID].platoonID].getNumInPlatoon(ID) != 1)
    {
        //following truck lane-changing
        if (vehiclesInNet[ID].lanechangestate == 1 && vehiclesInNet[ID].returnlanestate == 0)
        {
            Yaw_angle_error0 = vehiclesInNet[ID].laneAngle;
            Lat_position_error0 = (vehiclesInNet[ID].currentLane - 1) * vehiclesInNet[ID].lanewidth + vehiclesInNet[ID].lanewidth / 2 + vehiclesInNet[ID].lateralPosition;
            latcontrol(currentVehicle.timestep, Lat_position_error0, vehiclesInNet[ID].wheelangle, Yaw_angle_error0, Step_total, Mx->k0, Mx->Lat_position_tar, Mx->s, Mx->lat_slope,
                Mx->state_vector_lonspeed, Mx->Head_angle_tar, Mx->State_vector, platoons[vehiclesInNet[ID].platoonID].getNumInPlatoon(ID));

            vehiclesInNet[ID].wheelangle = Mx->State_vector(2, 1) - 0;

            if ((activelanechange == -1 && Mx->State_vector(1, 1) > 0)||(reltargetlane ==-1 && Mx->State_vector(1, 1) > 0))
            {
                Mx->State_vector(1, 1) = 0;
            }
            else if ((activelanechange == 1 && Mx->State_vector(1, 1) < 0)||(reltargetlane ==1 && Mx->State_vector(1, 1) < 0))
            {
                Mx->State_vector(1, 1) = 0;
            }

            if (vehiclesInNet[ID].currentLane == platoons[vehiclesInNet[ID].platoonID].targetlane) 
            {
                if (abs(vehiclesInNet[ID].lateralPosition) < 0.03 || vehiclesInNet[ID].MPCstep > 190) 
                {
                    vehiclesInNet[ID].lanechangestate = 0;
                    vehiclesInNet[ID].MPCstep = 0;
                    vehiclesInNet[ID].wheelangle = 0;
                    vehiclesInNet[ID].desiredLaneAngle = 0;

                    if (platoons[vehiclesInNet[ID].platoonID].lanechangejudgment(vehiclesInNet, platoons, vehiclesInNet[ID].platoonID)) 
                    {
                        platoons[vehiclesInNet[ID].platoonID].platoonlanechangestate = 0;
                        platoons[vehiclesInNet[ID].platoonID].currentlane = vehiclesInNet[ID].currentLane;
                    }
                    return 1;
                }
                else
                {
                    vehiclesInNet[ID].desiredLaneAngle = Mx->State_vector(1, 1);
                }
            }
            else
            {
                if (abs(vehiclesInNet[ID].lateralPosition) > (vehiclesInNet[ID].lanewidth / 2 + vehiclesInNet[ID].width / 2))
                {
                    vehiclesInNet[ID].setActiveLaneChange(platoons[vehiclesInNet[ID].platoonID].turndirection);
                    vehiclesInNet[ID].setRelativeTargetLane(platoons[vehiclesInNet[ID].platoonID].turndirection);
                }
                vehiclesInNet[ID].desiredLaneAngle = Mx->State_vector(1, 1);
            }
            vehiclesInNet[ID].MPCstep++;
            return 1;
        }
        else if (vehiclesInNet[ID].returnlanestate == 1)  
        {
            platoons[vehiclesInNet[ID].platoonID].platoonlanechangestate = 1;
            if (vehiclesInNet[ID].currentLane != platoons[vehiclesInNet[ID].platoonID].targetlane) 
            {
                vehiclesInNet[ID].setActiveLaneChange(0);
                vehiclesInNet[ID].setRelativeTargetLane(0);
            }
            else if (vehiclesInNet[ID].currentLane == platoons[vehiclesInNet[ID].platoonID].targetlane) 
            {
                vehiclesInNet[ID].setActiveLaneChange((platoons[vehiclesInNet[ID].platoonID].currentlane - platoons[vehiclesInNet[ID].platoonID].targetlane) < 0 ? -1 : 1);
                vehiclesInNet[ID].setRelativeTargetLane((platoons[vehiclesInNet[ID].platoonID].currentlane - platoons[vehiclesInNet[ID].platoonID].targetlane) < 0 ? -1 : 1);
            }
            Yaw_angle_error0 = vehiclesInNet[ID].laneAngle;
            if ((platoons[vehiclesInNet[ID].platoonID].currentlane - platoons[vehiclesInNet[ID].platoonID].targetlane) < 0 && vehiclesInNet[ID].laneAngle > 0)
            {
                Yaw_angle_error0 = 0;
            }
            else if ((platoons[vehiclesInNet[ID].platoonID].currentlane - platoons[vehiclesInNet[ID].platoonID].targetlane) > 0 && vehiclesInNet[ID].laneAngle < 0)
            {
                Yaw_angle_error0 = 0;
            }
            Lat_position_error0 = (vehiclesInNet[ID].currentLane - 1) * vehiclesInNet[ID].lanewidth + vehiclesInNet[ID].lanewidth / 2 + vehiclesInNet[ID].lateralPosition;
            latcontrol(currentVehicle.timestep, Lat_position_error0, vehiclesInNet[ID].wheelangle, Yaw_angle_error0, Step_total, Mx->k0, Mx->Lat_position_tar, Mx->s, Mx->lat_slope,
                Mx->state_vector_lonspeed, Mx->Head_angle_tar, Mx->State_vector, platoons[vehiclesInNet[ID].platoonID].getNumInPlatoon(ID));

            vehiclesInNet[ID].wheelangle = Mx->State_vector(2, 1) - 0;
            if ((activelanechange == 1 && Mx->State_vector(1, 1) < 0) || (vehiclesInNet[ID].activeLaneChange == 1 && Mx->State_vector(1, 1) < 0)||(reltargetlane == 1 && Mx->State_vector(1, 1) < 0))
            {
                Mx->State_vector(1, 1) = 0;
            }
            else if ((activelanechange == -1 && Mx->State_vector(1, 1) > 0) || (vehiclesInNet[ID].activeLaneChange == -1 && Mx->State_vector(1, 1) > 0)||(reltargetlane==-1 && Mx->State_vector(1, 1) > 0))
            {

                Mx->State_vector(1, 1) = 0;
            }
            vehiclesInNet[ID].desiredLaneAngle = Mx->State_vector(1, 1);
            if (abs(vehiclesInNet[ID].lateralPosition) < 0.03 && vehiclesInNet[ID].currentLane != platoons[vehiclesInNet[ID].platoonID].targetlane)  
            {
                vehiclesInNet[ID].lanechangestate = 0;
                vehiclesInNet[ID].returnlanestate = 0;
                vehiclesInNet[ID].MPCstep = 0;
                vehiclesInNet[ID].wheelangle = 0;
                vehiclesInNet[ID].desiredLaneAngle = 0;

                if (platoons[vehiclesInNet[ID].platoonID].lanechangereturnjudgment(vehiclesInNet, platoons, vehiclesInNet[ID].platoonID)) 
                {
                    platoons[vehiclesInNet[ID].platoonID].platoonlanechangestate = 0;
                }

                long frontID = platoons[vehiclesInNet[ID].platoonID].getFrontIDof(ID);
                SimVehicle platoonfrontvehicle = vehiclesInNet[frontID];
                if (vehiclesInNet[ID].currentLane != platoonfrontvehicle.currentLane && platoonfrontvehicle.returnlanestate == 0) 
                {
                    platoons[vehiclesInNet[ID].platoonID].splitPlatoon(platoons, vehiclesInNet[ID].platoonID, ID, vehiclesInNet);
                }

                return 1;
            }
            return 1;
        }
    }
    return 0;

}