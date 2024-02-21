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

namespace Dom._2_21621397
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'database1DataSet.Table' table. You can move, or remove it, as needed.
            this.tableTableAdapter.Fill(this.database1DataSet.Table);

        }

        string cs = @"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=|DataDirectory|\Database1.mdf;Integrated Security=True";
        SqlConnection sqlconn;
        SqlCommand sqlcomm;
        string Query;
        DataTable dt;
        SqlDataAdapter sqladapter;
        int ID = 0;

        private void DisplayData()
        {
            sqlconn = new SqlConnection(cs);
            Query = "SELECT * FROM [Table]";
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
            comboBox1.Text = "";
            comboBox1.SelectedItem = null;
            comboBox2.Text = "";
            comboBox2.SelectedItem = null;
            ID = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "" && textBox2.Text != "" && textBox3.Text != "" && comboBox1.SelectedItem != null && comboBox2.SelectedItem != null)
            {
                sqlconn = new SqlConnection(cs);
                sqlconn.Open();
                Query = "INSERT INTO [Table] (Id, Name, Family, Course, Speciality) VALUES (@Id, @Name, @Family, @Course, @Speciality)";
                sqlcomm = new SqlCommand(Query, sqlconn);
                sqlcomm.Parameters.AddWithValue("@Id", textBox1.Text);
                sqlcomm.Parameters.AddWithValue("@Name", textBox2.Text);
                sqlcomm.Parameters.AddWithValue("@Family", textBox3.Text);
                sqlcomm.Parameters.AddWithValue("@Course", comboBox1.SelectedItem);
                sqlcomm.Parameters.AddWithValue("@Speciality", comboBox2.SelectedItem);
                sqlcomm.ExecuteNonQuery();
                sqlconn.Close();
                MessageBox.Show("Inserted");
                DisplayData();
                ClearData();
            }
            else MessageBox.Show("Insert failed");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "" && textBox2.Text != "" && textBox3.Text != "" && comboBox1.SelectedItem != null && comboBox2.SelectedItem != null)
            {
                sqlconn = new SqlConnection(cs);
                sqlconn.Open();
                Query = "UPDATE [Table] SET Name=@Name, Family=@Family, Course=@Course, Speciality=@Speciality WHERE Id=@Id"; ;
                sqlcomm = new SqlCommand(Query, sqlconn);
                sqlcomm.Parameters.AddWithValue("@Id", textBox1.Text);
                sqlcomm.Parameters.AddWithValue("@Name", textBox2.Text);
                sqlcomm.Parameters.AddWithValue("@Family", textBox3.Text);
                sqlcomm.Parameters.AddWithValue("@Course", comboBox1.SelectedItem.ToString());
                sqlcomm.Parameters.AddWithValue("@Speciality", comboBox2.SelectedItem.ToString());
                sqlcomm.ExecuteNonQuery();
                sqlconn.Close();
                MessageBox.Show("Updated");
                DisplayData();
                ClearData();
            }
            else MessageBox.Show("Update failed");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (ID != 0)
            {
                sqlconn = new SqlConnection(cs);
                sqlconn.Open();
                Query = "DELETE [Table] WHERE Id = @Id";
                sqlcomm = new SqlCommand(Query, sqlconn);
                sqlcomm.Parameters.AddWithValue("@Id", ID);
                sqlcomm.ExecuteNonQuery();
                sqlconn.Close();
                MessageBox.Show("Delted");
                DisplayData();
                ClearData();
            }
            else MessageBox.Show("Delete failed");
        }

        private void dataGridView1_RowHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            ID = Convert.ToInt32(dataGridView1.Rows[e.RowIndex].Cells[0].Value);
            textBox1.Text = dataGridView1.Rows[e.RowIndex].Cells[0].Value.ToString();
            textBox2.Text = dataGridView1.Rows[e.RowIndex].Cells[1].Value.ToString();
            textBox3.Text = dataGridView1.Rows[e.RowIndex].Cells[2].Value.ToString();
            comboBox1.Text = dataGridView1.Rows[e.RowIndex].Cells[3].Value.ToString();
            comboBox2.Text = dataGridView1.Rows[e.RowIndex].Cells[4].Value.ToString();
        }
    }
}
