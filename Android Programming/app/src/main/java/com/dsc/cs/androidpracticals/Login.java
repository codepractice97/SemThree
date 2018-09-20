package com.dsc.cs.androidpracticals;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class Login extends AppCompatActivity implements View.OnClickListener{

    Button btn;
    EditText editText1, editText2;

    final String user_name = "mukul", pass = "mukul.singh";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        btn = findViewById(R.id.button_login);
        editText1 = findViewById(R.id.editText_name);
        editText2 = findViewById(R.id.editText_pass);

        btn.setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {
        String str1, str2;
        str1 = editText1.getText().toString();
        str2 = editText2.getText().toString();

        if (user_name.equals(str1) && pass.equals(str2))
            Toast.makeText(this, "Welcome " + user_name, Toast.LENGTH_LONG).show();
        else
            Toast.makeText(this, "Incorrect details", Toast.LENGTH_LONG).show();

    }
}
