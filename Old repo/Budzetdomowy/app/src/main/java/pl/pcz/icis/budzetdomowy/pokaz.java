package pl.pcz.icis.budzetdomowy;

import android.app.Activity;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Color;
import android.graphics.Typeface;
import android.os.Bundle;
import android.view.View;
import android.widget.Spinner;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;

/**
 * Created by Nefalem on 2015-04-11.
 */

public class pokaz extends Activity {
    //Context ctx=this;
    //TextView odczytka;
    Date data;
    SQLiteDatabase db;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.pokaz);
       /* if (savedInstanceState == null) {
            getSupportFragmentManager().beginTransaction()
                    .add(R.id.action_bar_container, new PlaceholderFragment())
                    .commit();
        }*/
        //odczytka= (TextView)findViewById(R.id.textView13);
        db=openOrCreateDatabase("Baza",MODE_PRIVATE, null);

    }

    public void clickDochody(View v) throws ParseException {
       // Date date = null;

        Cursor c=db.rawQuery("SELECT * from Dochody", null);
        int count= c.getCount();
        c.moveToFirst();
        TableLayout tableLayout = new TableLayout(getApplicationContext());
        tableLayout.setVerticalScrollBarEnabled(true);
        tableLayout.setBackgroundColor(Color.rgb(244, 196, 48));
        TableRow tableRow;
        TextView textView,textView1,textView2 = null,textView3,textView4,textView5,textView6,textView7,textView8,textView9;
        tableRow = new TableRow(getApplicationContext());
        textView=new TextView(getApplicationContext());
        textView.setText("Title");
        textView.setTextColor(Color.RED);
        textView.setTypeface(null, Typeface.BOLD);
        textView.setPadding(20, 20, 20, 20);
        tableRow.addView(textView);
        textView4=new TextView(getApplicationContext());
        textView4.setText("Date");
        textView4.setTextColor(Color.RED);
        textView4.setTypeface(null, Typeface.BOLD);
        textView4.setPadding(20, 20, 20, 20);
        tableRow.addView(textView4);
        textView5=new TextView(getApplicationContext());
        textView5.setText("Value");
        textView5.setTextColor(Color.RED);
        textView5.setTypeface(null, Typeface.BOLD);
        textView5.setPadding(20, 20, 20, 20);
        tableRow.addView(textView5);

        textView6=new TextView(getApplicationContext());
        textView6.setText("Status");
        textView6.setTextColor(Color.RED);
        textView6.setTypeface(null, Typeface.BOLD);
        textView6.setPadding(20, 20, 20, 20);
        tableRow.addView(textView6);

        textView7=new TextView(getApplicationContext());
        textView7.setText("Category");
        textView7.setTextColor(Color.RED);
        textView7.setTypeface(null, Typeface.BOLD);
        textView7.setPadding(20, 20, 20, 20);
        tableRow.addView(textView7);

        tableLayout.addView(tableRow);
        for (Integer j = 0; j < count; j++)
        {
            tableRow = new TableRow(getApplicationContext());
            textView1 = new TextView(getApplicationContext());
            textView1.setText(c.getString(c.getColumnIndex("title")));

            textView2 = new TextView(getApplicationContext());
            /*textView2.setText(str);*/

            //Konwersja
            String strdate = c.getString(c.getColumnIndex("date"));
            String currentPattern = "EEE MMM dd kk:mm:ss z yyyy";
            SimpleDateFormat sdf = new SimpleDateFormat( currentPattern, Locale.ENGLISH );

            Date dt = sdf.parse( strdate ); // new date is constructed
            System.out.println( dt );

            String newPattern = "dd-MM-yyyy";     // new pattern is defined
            sdf.applyPattern( newPattern );        // the same is applied
            String new_strdate = sdf.format( dt ); // on the date object

            textView2.setText(new_strdate);// resulting new string form of date
            //


            textView3 = new TextView(getApplicationContext());
            textView3.setText(c.getString(c.getColumnIndex("value")));

            textView8 = new TextView(getApplicationContext());
            textView8.setText(c.getString(c.getColumnIndex("status")));
            textView9 = new TextView(getApplicationContext());
            textView9.setText(c.getString(c.getColumnIndex("category")));

            textView1.setTextColor(Color.GREEN);
            textView2.setTextColor(Color.GREEN);
            textView3.setTextColor(Color.GREEN);
            textView8.setTextColor(Color.GREEN);
            textView9.setTextColor(Color.GREEN);

            textView1.setPadding(20, 20, 20, 20);
            textView2.setPadding(20, 20, 20, 20);
            textView3.setPadding(20, 20, 20, 20);

            textView8.setPadding(20, 20, 20, 20);
            textView9.setPadding(20, 20, 20, 20);

            tableRow.addView(textView1);
            tableRow.addView(textView2);
            tableRow.addView(textView3);

            tableRow.addView(textView8);
            tableRow.addView(textView9);

            tableLayout.addView(tableRow);
            c.moveToNext() ;
        }
        tableLayout.setBackgroundColor(Color.rgb(244,196,48));
        setContentView(tableLayout);
        db.close();
    }

    public void clickWydatki(View v) throws ParseException {
        // Date date = null;

        Cursor c=db.rawQuery("SELECT * from Wydatki", null);
        int count= c.getCount();
        c.moveToFirst();
        TableLayout tableLayout = new TableLayout(getApplicationContext());
        tableLayout.setVerticalScrollBarEnabled(true);
        tableLayout.setBackgroundColor(Color.rgb(244, 196, 48));
        TableRow tableRow;
        TextView textView,textView1,textView2 = null,textView3,textView4,textView5,textView6,textView7,textView8,textView9;
        tableRow = new TableRow(getApplicationContext());
        textView=new TextView(getApplicationContext());
        textView.setText("Title");
        textView.setTextColor(Color.RED);
        textView.setTypeface(null, Typeface.BOLD);
        textView.setPadding(20, 20, 20, 20);
        tableRow.addView(textView);
        textView4=new TextView(getApplicationContext());
        textView4.setText("Date");
        textView4.setTextColor(Color.RED);
        textView4.setTypeface(null, Typeface.BOLD);
        textView4.setPadding(20, 20, 20, 20);
        tableRow.addView(textView4);
        textView5=new TextView(getApplicationContext());
        textView5.setText("Value");
        textView5.setTextColor(Color.RED);
        textView5.setTypeface(null, Typeface.BOLD);
        textView5.setPadding(20, 20, 20, 20);
        tableRow.addView(textView5);

        textView6=new TextView(getApplicationContext());
        textView6.setText("Status");
        textView6.setTextColor(Color.RED);
        textView6.setTypeface(null, Typeface.BOLD);
        textView6.setPadding(20, 20, 20, 20);
        tableRow.addView(textView6);

        tableLayout.addView(tableRow);
        for (Integer j = 0; j < count; j++)
        {
            tableRow = new TableRow(getApplicationContext());
            textView1 = new TextView(getApplicationContext());
            textView1.setText(c.getString(c.getColumnIndex("title")));

            textView2 = new TextView(getApplicationContext());
            /*textView2.setText(str);*/

            //Konwersja
            String strdate = c.getString(c.getColumnIndex("date"));
            String currentPattern = "EEE MMM dd kk:mm:ss z yyyy";
            SimpleDateFormat sdf = new SimpleDateFormat( currentPattern, Locale.ENGLISH );

            Date dt = sdf.parse( strdate ); // new date is constructed
            System.out.println( dt );

            String newPattern = "dd-MM-yyyy";     // new pattern is defined
            sdf.applyPattern( newPattern );        // the same is applied
            String new_strdate = sdf.format( dt ); // on the date object

            textView2.setText(new_strdate);// resulting new string form of date
            //


            textView3 = new TextView(getApplicationContext());
            textView3.setText(c.getString(c.getColumnIndex("value")));

            textView8 = new TextView(getApplicationContext());
            textView8.setText(c.getString(c.getColumnIndex("status")));

            textView1.setTextColor(Color.GREEN);
            textView2.setTextColor(Color.GREEN);
            textView3.setTextColor(Color.GREEN);
            textView8.setTextColor(Color.GREEN);

            textView1.setPadding(20, 20, 20, 20);
            textView2.setPadding(20, 20, 20, 20);
            textView3.setPadding(20, 20, 20, 20);

            textView8.setPadding(20, 20, 20, 20);

            tableRow.addView(textView1);
            tableRow.addView(textView2);
            tableRow.addView(textView3);

            tableRow.addView(textView8);

            tableLayout.addView(tableRow);
            c.moveToNext() ;
        }
        tableLayout.setBackgroundColor(Color.rgb(244,196,48));
        setContentView(tableLayout);
        db.close();
    }

    public void zestawka(View v) throws ParseException {
        int l1=0,l2=0,wynik1;int a=0;
        Calendar c =Calendar.getInstance();
        Spinner spin1 = (Spinner)findViewById(R.id.spinner);

        if(spin1.getSelectedItem().equals("Ostatni Tydzień"))
            a=7;
        if(spin1.getSelectedItem().equals("Ostatni Miesiąc"))
            a=30;
        if(spin1.getSelectedItem().equals("Ostatni rok"))
            a=365;

        Date datka=new Date(c.get(Calendar.YEAR),c.get(Calendar.MONTH),c.get(Calendar.DAY_OF_MONTH));

        String currentPattern = "EEE MMM dd kk:mm:ss z yyyy";
        String newPattern = "dd-MM-yyyy";
        Cursor c1=db.rawQuery("SELECT * from Dochody", null);
        Cursor c2=db.rawQuery("SELECT * from Wydatki", null);
        int count1= c1.getCount();
        c1.moveToFirst();
        int count2= c2.getCount();
        c2.moveToFirst();
        TableLayout tableLayout = new TableLayout(getApplicationContext());
        tableLayout.setVerticalScrollBarEnabled(true);
        tableLayout.setBackgroundColor(Color.rgb(244, 196, 48));
        TableRow tableRow;
        TextView textView,textView1,textView2 = null,textView4,textView5;

        tableRow = new TableRow(getApplicationContext());
        textView=new TextView(getApplicationContext());
        textView.setText("Dochód");
        textView.setTextColor(Color.RED);
        textView.setTypeface(null, Typeface.BOLD);
        textView.setPadding(20, 20, 20, 20);
        tableRow.addView(textView);

        textView4=new TextView(getApplicationContext());
        textView4.setText("Wydatki");
        textView4.setTextColor(Color.RED);
        textView4.setTypeface(null, Typeface.BOLD);
        textView4.setPadding(20, 20, 20, 20);
        tableRow.addView(textView4);

        textView1=new TextView(getApplicationContext());
        textView1.setText("Kasa do dyspozycji");
        textView1.setTextColor(Color.RED);
        textView1.setTypeface(null, Typeface.BOLD);
        textView1.setPadding(20, 20, 20, 20);
        tableRow.addView(textView1);

        tableLayout.addView(tableRow);
        for (Integer j = 0; j < count1; j++)
        {
            String strdate1 = c1.getString(c1.getColumnIndex("date"));
            SimpleDateFormat sdf1 = new SimpleDateFormat( currentPattern, Locale.ENGLISH );
            Date dt = sdf1.parse( strdate1 );
            sdf1.applyPattern( newPattern );
            if(datka.getTime()-dt.getTime()>a){
                if(a==365)
                    for(int i=0;i<11;i++)
                        l1=l1+c1.getInt(c1.getColumnIndex("value"));
                l1=l1+c1.getInt(c1.getColumnIndex("value"));
            }

            c1.moveToNext() ;

        }
        for (Integer j = 0; j < count2; j++)
        {
            String strdate2 = c2.getString(c2.getColumnIndex("date"));
            SimpleDateFormat sdf2 = new SimpleDateFormat( currentPattern, Locale.ENGLISH );
            Date dt1 = sdf2.parse( strdate2 );
            sdf2.applyPattern( newPattern );
            if(datka.getTime()-dt1.getTime()>a){
                if(a==365)
                    for(int i=0;i<11;i++)
                        l2=l2+c2.getInt(c2.getColumnIndex("value"));
                l2=l2+c2.getInt(c2.getColumnIndex("value"));
            }


            c2.moveToNext() ;
        }
        wynik1=l1-l2;

        tableRow = new TableRow(getApplicationContext());
        textView2 = new TextView(getApplicationContext());
        textView2.setText(""+l1);
        textView4 = new TextView(getApplicationContext());
        textView4.setText(""+l2);
        textView5 = new TextView(getApplicationContext());
        textView5.setText(""+wynik1);

        textView2.setTextColor(Color.GREEN);
        textView4.setTextColor(Color.GREEN);
        textView5.setTextColor(Color.GREEN);

        textView2.setPadding(20, 20, 20, 20);
        textView4.setPadding(20, 20, 20, 20);
        textView5.setPadding(20, 20, 20, 20);

        tableRow.addView(textView2);
        tableRow.addView(textView4);
        tableRow.addView(textView5);
        tableLayout.addView(tableRow);
        tableLayout.setBackgroundColor(Color.rgb(244,196,48));
        setContentView(tableLayout);
        db.close();
    }
   /*  @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
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
            startActivity (new Intent (this, edytuj.class));
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
            View rootView = inflater.inflate(R.layout.pokaz, action_bar_container, false);
            return rootView;
        }
    }*/
}
