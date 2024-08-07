using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace diamond.ViewModel
{
    class MainPageRC<T> : ICommand
    {
        readonly Action<T>? _excute;        
        
        readonly Predicate<T>? _predicate;
        
        private MainPageVMD m;               

        public MainPageRC(Action<T>? excute, Predicate<T>? predicate,MainPageVMD mainPageVMD=null)
        {
            _excute = excute;
            _predicate = predicate;
            m = mainPageVMD;
        }
        
        public MainPageRC(Action<T> action):this(action,null) 
        {
               
        }

        public event EventHandler? CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }
            
        public bool CanExecute(object? parameter)
        {
                                  
            if (_predicate==null) 
            {
                return true;
            }
        
            return _predicate((T)parameter);
        }

        public void Execute(object? parameter)
        {            
            if (_excute != null)
            {
                _excute((T)parameter);
            }

        }
       
    }
}
