using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection.Metadata;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Navigation;
using diamond.VIew;
using diamond.Model;
using System.Net.Sockets;
using System.Text.Json.Nodes;
using Newtonsoft.Json;
namespace diamond.ViewModel
{
    public class MainPageVMD :INotifyPropertyChanged
    {
        private string idstring;
        public TcpSockets tcpSockets {  get; set; }
        private string pwstring;
        private int changepwlen;
        public string IDString { get { return idstring; } set { idstring = value; Notify(nameof(IDString)); } }
        public string PWString { get { return pwstring; } set { pwstring = value; Notify(nameof(PWString)); } }
        public string RealPW { get; set; }
        public ICommand Login { get;set; }
        public ICommand Sign {  get;set; }
        public MainWindowViewModel transform { get; set; }
        
        public MainPageVMD( MainWindowViewModel mainWindowViewModel)
        {
            transform = mainWindowViewModel;
            Login = new MainPageRC<object>(Loginbtnclk,PWLenCheck);            
            Sign = new MainPageRC<object>(Sign_Up, null);
            tcpSockets = new TcpSockets();
            tcpSockets.Soc = transform.Tcpsokcets.Soc;
            while (tcpSockets.Soc == null)
                if (tcpSockets.Soc != null) break;
        }


        private void Sign_Up(object? param)
        {
            Window window = new Window1();
            window.Show();
        }
                
        private void Loginbtnclk(object? param)
        {
            PasswordBox? passwordBox = param as PasswordBox;
            if (IDString != null)
            {
                var id_pw = new
                {
                    protocol = "로그인",
                    id = IDString,
                    pw = passwordBox.Password
                };

                byte[] bytearray = new byte[4000];
                bytearray = Encoding.UTF8.GetBytes(Newtonsoft.Json.JsonConvert.SerializeObject(id_pw));
                tcpSockets.Soc.Send(bytearray);
                
                Array.Clear(bytearray, 0, bytearray.Length);

                tcpSockets.Soc.Receive(bytearray);
                    
                string result = Encoding.UTF8.GetString(bytearray);
                result = result.Replace("\0", string.Empty);
                result += "\0";
                transform.UserName = result;
                if (result.CompareTo("로그인실패") == 0)
                    MessageBox.Show("로그인 실패");
                else
                {
                    MessageBox.Show("로그인성공");
                    transform.FrameChange = 1;

                }


            }
            else
                MessageBox.Show("ID를 입력해주세요");
        }

        
        bool PWLenCheck(object? param)
        {   
            PasswordBox passwordBox = param as PasswordBox;
            if (param == null)
            {                        
                return false;
            }
            
            return passwordBox.Password.Length >= 10 ? true : false;
        }

        private void Notify([CallerMemberName] String name = "")
        {
            PropertyChanged?.Invoke(this,new PropertyChangedEventArgs(name));
        }
        
        public event PropertyChangedEventHandler? PropertyChanged;
        
    }

}
