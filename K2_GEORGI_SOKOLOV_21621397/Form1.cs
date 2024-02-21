using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace K2_GEORGI_SOKOLOV_21621397
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'database1DataSet.Slujiteli' table. You can move, or remove it, as needed.
            this.slujiteliTableAdapter.Fill(this.database1DataSet.Slujiteli);
            //Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=C:\Users\gmsokolov\source\repos\K2_GEORGI_SOKOLOV_21621397\Database1.mdf;Integrated Security=True
        }

        string cs = @"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=C:\Users\gmsokolov\source\repos\K2_GEORGI_SOKOLOV_21621397\Database1.mdf;Integrated Security=True";
        SqlConnection sqlconn;
        SqlCommand sqlcomm;
        string Query;
        DataTable dt;
        SqlDataAdapter sqladapter;
        int ID = 0;

        private void DisplayData()
        {
            sqlconn = new SqlConnection(cs);
            Query = "SELECT * FROM Slujiteli";
            sqlcomm = new SqlCommand(Query, sqlconn);
            sqladapter = new SqlDataAdapter();
            dt = new DataTable();
            sqladapter.SelectCommand = sqlcomm;
            sqladapter.Fill(dt);
            dataGridView1.DataSource = dt;
        }

        private void ClearData()
        {
            textBox1.Text = "";
            textBox2.Text = "";
            textBox3.Text = "";
            textBox4.Text = "";
            textBox5.Text = "";
            textBox6.Text = "";
            textBox7.Text = "";
            comboBox1.SelectedIndex = -1;
            comboBox2.SelectedIndex = -1;
            comboBox3.SelectedIndex = -1;
            comboBox4.SelectedIndex = -1;
            ID = 0;
        }

        private void dataGridView1_RowHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            ID = Convert.ToInt32(dataGridView1.Rows[e.RowIndex].Cells[0].Value);
            textBox1.Text = dataGridView1.Rows[e.RowIndex].Cells[0].Value.ToString();
            textBox2.Text = dataGridView1.Rows[e.RowIndex].Cells[1].Value.ToString();
            textBox3.Text = dataGridView1.Rows[e.RowIndex].Cells[2].Value.ToString();
            textBox4.Text = dataGridView1.Rows[e.RowIndex].Cells[3].Value.ToString();
            textBox5.Text = dataGridView1.Rows[e.RowIndex].Cells[4].Value.ToString();
            textBox6.Text = dataGridView1.Rows[e.RowIndex].Cells[5].Value.ToString();
            textBox7.Text = dataGridView1.Rows[e.RowIndex].Cells[6].Value.ToString();
            comboBox1.Text = dataGridView1.Rows[e.RowIndex].Cells[7].Value.ToString();
            comboBox2.Text = dataGridView1.Rows[e.RowIndex].Cells[8].Value.ToString();
        }

        //Нов служител
        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "" && textBox2.Text != "" && textBox3.Text != "" 
                && textBox4.Text != "" && textBox5.Text != "" && textBox6.Text != "" && textBox7.Text != ""
                && comboBox1.SelectedItem != null && comboBox2.SelectedItem != null
                && !(int.Parse(textBox5.Text) < 30 && int.Parse(textBox7.Text) >= 1200))
            {
                sqlconn = new SqlConnection(cs);
                sqlconn.Open();
                Query = "INSERT INTO Slujiteli (EGN, Ime, Familiya, Telefon, Vuzrast, Staj, Zaplata, Otdel, Obrazovanie) " +
                    "VALUES (@EGN, @Ime, @Familiya, @Telefon, @Vuzrast, @Staj, @Zaplata, @Otdel, @Obrazovanie)";
                sqlcomm = new SqlCommand(Query, sqlconn);
                sqlcomm.Parameters.AddWithValue("@EGN", textBox1.Text);
                sqlcomm.Parameters.AddWithValue("@Ime", textBox2.Text);
                sqlcomm.Parameters.AddWithValue("@Familiya", textBox3.Text);
                sqlcomm.Parameters.AddWithValue("@Telefon", textBox4.Text);
                sqlcomm.Parameters.AddWithValue("@Vuzrast", textBox5.Text);
                sqlcomm.Parameters.AddWithValue("@Staj", textBox6.Text);
                sqlcomm.Parameters.AddWithValue("@Zaplata", textBox7.Text);
                sqlcomm.Parameters.AddWithValue("@Otdel", comboBox1.SelectedItem);
                sqlcomm.Parameters.AddWithValue("@Obrazovanie", comboBox2.SelectedItem);
                sqlcomm.ExecuteNonQuery();
                sqlconn.Close();
                MessageBox.Show("Успешно добавяне");
                DisplayData();
                ClearData();
            }
            else MessageBox.Show("Неспешно добавяне");
        }

        //Изтрй служител
        private void button2_Click(object sender, EventArgs e)
        {
            if (ID != 0 && int.Parse(textBox5.Text) > 65 && int.Parse(textBox6.Text) > 40)
            {
                sqlconn = new SqlConnection(cs);
                sqlconn.Open();
                Query = "DELETE Slujiteli WHERE EGN = @EGN";
                sqlcomm = new SqlCommand(Query, sqlconn);
                sqlcomm.Parameters.AddWithValue("@EGN", ID);
                sqlcomm.ExecuteNonQuery();
                sqlconn.Close();
                MessageBox.Show("Успешно изтриване");
                DisplayData();
                ClearData();
            }
            else MessageBox.Show("Неуспешно изтриване");
        }

        //Промени образование
        private void button3_Click(object sender, EventArgs e)
        {
            if(comboBox3.SelectedIndex != -1 && comboBox2.SelectedItem != null)
            {
               
            }
            else MessageBox.Show("Неуспешна промяна");
        }

        //Филтрирай по отдел
        private void button4_Click(object sender, EventArgs e)
        {
            if (comboBox4.SelectedItem != null)
            {
                sqlconn = new SqlConnection(cs);
                Query = "SELECT * FROM Slujiteli WHERE Otdel = @Otdel";
                sqlcomm = new SqlCommand(Query, sqlconn);
                sqlcomm.Parameters.AddWithValue("@Otdel", comboBox4.SelectedItem.ToString());
                sqladapter = new SqlDataAdapter();
                dt = new DataTable();
                sqladapter.SelectCommand = sqlcomm;
                sqladapter.Fill(dt);
                dataGridView1.DataSource = dt;
            }
            else MessageBox.Show("Неуспешно филтриране");
        }
    }
}
