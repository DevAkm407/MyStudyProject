using diamond.VIew;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using diamond.Model;
using System.Net.Sockets;
using System.Net;

namespace diamond.ViewModel
{
    public class MainWindowViewModel : INotifyPropertyChanged
    {
      
        public TcpSockets Tcpsokcets { get; set; }
        public string UserName {  get; set; }
        enum Dataframe {_mainpage=0,sp,price,history};        
        
        public int FrameChange {  get; set; }
        
        public MainWindowViewModel() 
        {
            Tcpsokcets = new TcpSockets();
            Tcpsokcets.Soc = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            var myserver = IPAddress.Parse("10.10.21.122");
            Tcpsokcets.Soc.Connect(myserver, 10001);
            Thread t1 = new Thread(new ThreadStart(framcheck));
            t1.Start();            
        }

        private void framcheck()
        {
            this.FrameChange = 0;
            int last=this.FrameChange;
            this.ContentView = new MainPageVMD(this);
            while (true)
            {
                if (this.FrameChange != last) 
                {
                    switch (FrameChange)
                    {
                        case (int)Dataframe._mainpage:
                            this.ContentView = new MainPageVMD(this);
                            break;
                        case (int)Dataframe.sp:
                            this.ContentView = new Select_Page_VMD(this);
                            break;
                        case (int)Dataframe.price:
                            this.ContentView = new Price_VMD(this);
                            break;
                        case (int)Dataframe.history:
                            this.ContentView = new History_VMD(this);
                            break;
                    }                    
                    last=this.FrameChange;
                }
                Thread.Sleep(200);    
            }
        }

        public object _contentView;

      
        public object ContentView
        {
            get { return this._contentView; }
            set { this._contentView = value; this.Notify(nameof(ContentView)); }
        }

        #region INotifyPropertyChanged Members

        private void Notify([CallerMemberName] String name = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
        public event PropertyChangedEventHandler? PropertyChanged;
        #endregion
    }
}
