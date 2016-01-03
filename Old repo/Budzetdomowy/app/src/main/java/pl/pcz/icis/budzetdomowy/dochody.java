package pl.pcz.icis.budzetdomowy;

import android.app.ActionBar;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.app.ActionBarActivity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Created by Nefalem on 2015-04-02.
 */

public class dochody extends Activity {
    EditText EDITKA1,EDITKA2,EDITKA3;
    CheckBox CHECK1,CHECK2;
    Spinner spin1;
    SQLiteDatabase db;
    String title,kat,stability;
    int values;
    Context ctx=this;
    Date data;
    String data_str;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.dochody);
        //fun1();
        /*if (savedInstanceState == null) {
            getSupportFragmentManager().beginTransaction()
                    .add(R.id.container, new PlaceholderFragment())
                    .commit();
        }*/
        EDITKA1=(EditText)findViewById(R.id.editText);
        EDITKA2=(EditText)findViewById(R.id.editText2);
        EDITKA3=(EditText)findViewById(R.id.editText3);
        CHECK1=(CheckBox)findViewById(R.id.checkBox);
        CHECK2=(CheckBox)findViewById(R.id.checkBox2);
        spin1=(Spinner)findViewById(R.id.rozw);
        db=openOrCreateDatabase("Baza",MODE_PRIVATE, null);
        db.execSQL("CREATE TABLE IF NOT EXISTS Dochody(id INTEGER PRIMARY KEY, title VARCHAR,date DATE,value INT,status VARCHAR,category VARCHAR);");
    }

       public void onButtonikClick(View v) throws ParseException {
           title=EDITKA1.getText().toString();

           //data
           data_str = EDITKA2.getText().toString();

           // konwersja ze stringa na date.
           SimpleDateFormat dt = new SimpleDateFormat("dd-MM-yyyy");
           //String data_str = c.getString(c.getColumnIndex("date"));
           data = dt.parse(data_str);

           //SimpleDateFormat dt = new SimpleDateFormat("dd-mm-yyyy");
           //data = dt.parse(data_str);
           //konwersja ze stringa na inta.
           values=Integer.parseInt(EDITKA3.getText().toString());

           if(CHECK1.isChecked())
           stability="stały";
           if(CHECK2.isChecked())
           stability = "zmienny";
           kat=spin1.getSelectedItem().toString();
           db.execSQL("INSERT INTO  Dochody VALUES(NULL,'" + title + "','" + data + "','" + values + "','" + stability + "','" + kat + "');");
           //Toast.makeText(getApplicationContext()," string ="+data_str+" data="+dt.toString()+" data="+data+"", Toast.LENGTH_LONG).show();

           Toast.makeText(getApplicationContext()," "+title+" "+data+" " +values+" "+stability+" "+kat+" ", Toast.LENGTH_LONG).show();
        }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int itemId = item.getItemId();
        if (itemId == R.id.glowna) {
            startActivity (new Intent (this, main.class));
            return true;
        }
        if(itemId == R.id.dodusu1){
            startActivity (new Intent (this, dochody.class));
            return true;
        }
        if(itemId == R.id.dodusu2){
            startActivity (new Intent (this, wydatki.class));
            return true;
        }
        if(itemId == R.id.statystyki){
            startActivity (new Intent (this, pokaz.class));
            return true;
        }
        if(itemId == R.id.edytuj){
            startActivity (new Intent (this, dochody.class));
            return true;
        }
        else{
            return super.onOptionsItemSelected(item);
        }
    }

    public static class PlaceholderFragment extends Fragment {

        public PlaceholderFragment() {
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup action_bar_container,
                                 Bundle savedInstanceState) {
            View rootView = inflater.inflate(R.layout.dochody, action_bar_container, false);
            return rootView;
        }
    }
}
