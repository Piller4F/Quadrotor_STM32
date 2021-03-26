package com.example.sec_view;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;




public class MainActivity extends AppCompatActivity {
    com.example.sec_view.MyRockerView myRockerViewXY;
    com.example.sec_view.MyRockerView myRockerViewZ;

    //定义变量准备与布局文件中的部件关联起来
    private String directionXY;           //定义一个字符串变量来接收左侧摇杆的方向
    private TextView directionXY_Text;    //定义用于显示左侧摇杆方向的文本框
    private TextView angleXY_Text;        //定义用于显示左侧摇杆角度的文本框
    private TextView levelXY_Text;        //定义用于显示左侧摇杆距离摇杆中心距离的文本框
    private String angleXY;               //定义一个字符串变量来接收左侧摇杆的角度
    private String levelXY;               //定义一个字符串变量来接收左侧摇杆距离中心的距离

    private  String directionZ;           //定义一个字符串变量来接收的右侧摇杆方向
    private  String angleZ;               //定义一个字符串变量来接收右侧摇杆的角度
    private  String levelZ;               //定义一个字符串变量来接收右侧摇杆距离中心的距离
    private TextView directionZ_Text;     //定义用于显示右侧摇杆方向的文本框
    private TextView angleZ_Text;         //定义用于显示右侧摇杆角度的文本框
    private TextView levelZ_Text;         //定义用于显示左侧摇杆距离摇杆中心距离的文本框
    private static final String TAG = "RockerView";         //定义常量TAG

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);       //调用其父类Activity的onCreate方法来实现对界面的图画绘制工作(加载组件)
        setContentView(R.layout.rocker_);         //关联rocker.xml布局文件

        directionXY_Text = (TextView) findViewById(R.id.directionXY_Text);          //关联layout文件中对应的文本框
        angleXY_Text = (TextView) findViewById(R.id.angleXY_Text);
        levelXY_Text = (TextView) findViewById(R.id.levelXY_Text);

        directionZ_Text = (TextView) findViewById(R.id.directionZ_Text);
        angleZ_Text = (TextView) findViewById(R.id.angleZ_Text);
        levelZ_Text = (TextView) findViewById(R.id.levelZ_Text);

        myRockerViewXY = findViewById(R.id.rockerXY_View);                          //分别关联左右两个自定义摇杆组件
        myRockerViewZ = findViewById(R.id.rockerZ_View);

        myRockerViewZ.setOnShakeListener(MyRockerView.DirectionMode.DIRECTION_4_ROTATE_45, new MyRockerView.OnShakeListener() {
            @Override
            public void onStart() {

            }

            @Override
            public void direction(MyRockerView.Direction direction) {                   //获取摇杆的方向并将其保存在定义的directionz中
                if (direction == MyRockerView.Direction.DIRECTION_CENTER) {
                    directionZ = ("当前方向：中心");
                } else if (direction == MyRockerView.Direction.DIRECTION_DOWN) {
                    directionZ = ("当前方向：下");
                } else if (direction == MyRockerView.Direction.DIRECTION_LEFT) {
                    directionZ = ("当前方向：左");
                } else if (direction == MyRockerView.Direction.DIRECTION_UP) {
                    directionZ = ("当前方向：上");
                } else if (direction == MyRockerView.Direction.DIRECTION_RIGHT) {
                    directionZ = ("当前方向：右");
                } else if (direction == MyRockerView.Direction.DIRECTION_DOWN_LEFT) {
                    directionZ = ("当前方向：左下");
                } else if (direction == MyRockerView.Direction.DIRECTION_DOWN_RIGHT) {
                    directionZ = ("当前方向：右下");
                } else if (direction == MyRockerView.Direction.DIRECTION_UP_LEFT) {
                    directionZ = ("当前方向：左上");
                } else if (direction == MyRockerView.Direction.DIRECTION_UP_RIGHT) {
                    directionZ = ("当前方向：右上");
                }
                Log.e(TAG, "Z轴" + directionZ);                              //日志文件，不在软件中显示，显示在logcat中，显示directionz的值（右摇杆的方向）
                Log.e(TAG, "-----------------------------------------------");


                directionZ_Text.setText(directionZ);                                //在文本框中显示右摇杆的方向
        }


            @Override
            public void onFinish() {

            }
        });

        myRockerViewZ.setOnAngleChangeListener(new MyRockerView.OnAngleChangeListener() {   //监听角度变化
            @Override
            public void onStart() {

            }

            @Override
            public void angle(double angle) {
                angleZ = ("当前角度："+angle);                                   //获取右摇杆的角度放入定义的angleZ中
                Log.e(TAG, "Z轴"+angleZ);
                angleZ_Text.setText(angleZ);                                    //在文本框中显示右摇杆的角度
            }

            @Override
            public void onFinish() {

            }
        });
//级别
        myRockerViewZ.setOnDistanceLevelListener(new MyRockerView.OnDistanceLevelListener() {       //监听距离的变化
            @Override
            public void onDistanceLevel(int level) {
                levelZ = ("当前距离级别："+level);                             //获取右摇杆的距离放入定义的levelZ中
                Log.e(TAG, "Z轴"+levelZ);
                levelZ_Text.setText(levelZ);                                 //在文本框中显示右摇杆的距离级别
            }
        });

        myRockerViewXY.setOnShakeListener(MyRockerView.DirectionMode.DIRECTION_4_ROTATE_45, new MyRockerView.OnShakeListener() {
            @Override
            public void onStart() {

            }

            @Override
            public void direction(MyRockerView.Direction direction) {
                if (direction == MyRockerView.Direction.DIRECTION_CENTER){
                    directionXY = ("当前方向：中心");
                }else if (direction == MyRockerView.Direction.DIRECTION_DOWN){
                    directionXY = ("当前方向：下");
                }else if (direction == MyRockerView.Direction.DIRECTION_LEFT){
                    directionXY = ("当前方向：左");
                }else if (direction == MyRockerView.Direction.DIRECTION_UP){
                    directionXY = ("当前方向：上");
                }else if (direction == MyRockerView.Direction.DIRECTION_RIGHT){
                    directionXY = ("当前方向：右");
                }else if (direction == MyRockerView.Direction.DIRECTION_DOWN_LEFT){
                    directionXY = ("当前方向：左下");
                }else if (direction == MyRockerView.Direction.DIRECTION_DOWN_RIGHT){
                    directionXY = ("当前方向：右下");
                }else if (direction == MyRockerView.Direction.DIRECTION_UP_LEFT){
                    directionXY = ("当前方向：左上");
                }else if (direction == MyRockerView.Direction.DIRECTION_UP_RIGHT){
                    directionXY = ("当前方向：右上");
                }
                Log.e(TAG, "XY轴"+directionXY);
                Log.e(TAG, "-----------------------------------------------" );

               directionXY_Text.setText(directionXY);
            }

            @Override
            public void onFinish() {

            }
        });
//角度
        myRockerViewXY.setOnAngleChangeListener(new MyRockerView.OnAngleChangeListener() {
            @Override
            public void onStart() {

            }

            @Override
            public void angle(double angle) {
                angleXY = ("当前角度："+angle);
                Log.e(TAG, "XY轴"+angleXY);
               angleXY_Text.setText(angleXY);
            }

            @Override
            public void onFinish() {

            }
        });
//级别
        myRockerViewXY.setOnDistanceLevelListener(new MyRockerView.OnDistanceLevelListener() {
            @Override
            public void onDistanceLevel(int level) {
                levelXY = ("当前距离级别："+level);
                Log.e(TAG, "XY轴"+levelXY);
               levelXY_Text.setText(levelXY);
            }
        });
    }
}