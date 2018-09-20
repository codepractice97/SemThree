package com.dsc.cs.androidpracticals;

import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class ThreeBackground extends AppCompatActivity implements View.OnClickListener{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_three_background);

        findViewById(R.id.button_red).setOnClickListener(this);
        findViewById(R.id.button_green).setOnClickListener(this);
        findViewById(R.id.button_blue).setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()){
            case R.id.button_red:
                findViewById(R.id.three_canvas).setBackgroundColor(Color.RED);
                break;
            case R.id.button_green:
                findViewById(R.id.three_canvas).setBackgroundColor(Color.GREEN);
                break;
            case R.id.button_blue:
                findViewById(R.id.three_canvas).setBackgroundColor(Color.BLUE);
                break;
        }
    }
}
