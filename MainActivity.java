package com.example.smarthomeiot;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.CompoundButton;
import android.widget.TextView;
import android.widget.ToggleButton;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import org.w3c.dom.Text;

public class MainActivity extends AppCompatActivity {

    TextView distance;
    TextView ldr;
    ToggleButton btn1;
    ToggleButton btn2;

    String valueDistance;
    String valueLdr;
    String valueLed1;
    String valueLed2;

    DatabaseReference databaseReference;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        distance = (TextView) findViewById(R.id.distance);
        ldr = (TextView) findViewById((R.id.ldr));
        btn1 = (ToggleButton) findViewById(R.id.btn1);
        btn2 = (ToggleButton) findViewById(R.id.btn2);

        databaseReference = FirebaseDatabase.getInstance().getReference();

        databaseReference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                valueDistance = dataSnapshot.child("Node1/distance").getValue().toString();
                distance.setText("Distance: "+valueDistance);
                valueLdr = dataSnapshot.child("Node1/ldr").getValue().toString();
                ldr.setText("LDR : "+valueLdr);

                valueLed1 = dataSnapshot.child("Node1/distance").getValue().toString();
                if(Integer.parseInt(valueLed1) > 10)
                    btn1.setChecked(false);
                else
                    btn1.setChecked(true);

                valueLed2 = dataSnapshot.child("Node1/ldr").getValue().toString();
                if(Integer.parseInt(valueLed2) <= 500)
                    btn2.setChecked(false);
                else
                    btn2.setChecked(true);
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        btn1.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    DatabaseReference led1Ref = FirebaseDatabase.getInstance().getReference("Node1/led1");
                    led1Ref.setValue(1);
                }
                else
                {
                    DatabaseReference led1Ref = FirebaseDatabase.getInstance().getReference("Node1/led1");
                    led1Ref.setValue(0);
                }
            }
        });

        btn2.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    DatabaseReference led2Ref = FirebaseDatabase.getInstance().getReference("Node1/led2");
                    led2Ref.keepSynced(true);
                    led2Ref.setValue(1);
                }
                else
                {
                    DatabaseReference led2Ref = FirebaseDatabase.getInstance().getReference("Node1/led2");
                    led2Ref.keepSynced(true);
                    led2Ref.setValue(0);
                }
            }
        });
    }
}

