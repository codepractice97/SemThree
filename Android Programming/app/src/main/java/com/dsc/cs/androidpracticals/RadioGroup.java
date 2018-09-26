package com.dsc.cs.androidpracticals;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class RadioGroup extends AppCompatActivity {

    android.widget.RadioGroup radioGroup;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_radio_group);

        radioGroup = findViewById(R.id.radio_group);

        radioGroup.setOnCheckedChangeListener(new android.widget.RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(android.widget.RadioGroup radioGroup, int i) {
                String msg = "";
                if (i == R.id.radio_button_1)
                    msg += "Dr. Neeru Bhandari";
                else if (i == R.id.radio_button_2)
                    msg += "Dr. BB Singh";
                else if (i == R.id.radio_button_3)
                    msg += "Ms. Kanika Bajaj";
                else if (i == R.id.radio_button_4)
                    msg += "Dr. Anita Goel";
                else if (i == R.id.radio_button_5)
                    msg += "Ms. Vandana Tulsyan";
                else if (i == R.id.radio_button_6)
                    msg += "Ms. Simran Chadha";
                else if (i == R.id.radio_button_7)
                    msg += "Dr. Shweta Shani";
                else if (i == R.id.radio_button_8)
                    msg += "Dr. Prem Kumari Tiwari";
                else if (i == R.id.radio_button_9)
                    msg += "Mr. Santanu Kumar Das";
                else if (i == R.id.radio_button_10)
                    msg += "Ms. Ishwar Rani";
                else if (i == R.id.radio_button_11)
                    msg += "Dr. Seema Bose";
                else if (i == R.id.radio_button_12)
                    msg += "Mr. Sandeep Mehta";
                else if (i == R.id.radio_button_13)
                    msg += "Dr. Sadhna Srivastava";
                else if (i == R.id.radio_button_14)
                    msg += "Mr. Vivek Ratna";
                else if (i == R.id.radio_button_15)
                    msg += "Dr. VP Aggarwal";
                ((TextView)(findViewById(R.id.radio_button_selected))).setText(msg);
            }
        });
    }
}
