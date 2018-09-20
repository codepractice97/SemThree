package com.dsc.cs.androidpracticals;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class ImplicitIntent extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_implicit_intent);

        final EditText editText = findViewById(R.id.implicit_intent_data);
        Button button = findViewById(R.id.implicit_send_bt);

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(Intent.ACTION_SEND);
                intent.setType("text/plain");
                intent.putExtra(Intent.EXTRA_TEXT, editText.getText().toString());
                intent.putExtra(Intent.EXTRA_SUBJECT, "greeting!");
                startActivity(Intent.createChooser(intent, "Send Message"));
            }
        });
    }
}
