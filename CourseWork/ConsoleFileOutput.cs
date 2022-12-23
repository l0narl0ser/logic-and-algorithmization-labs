using System;
using System.IO;
using System.Text;

namespace MultiConsoleOutput
{
    public class ConsoleFileOutput : TextWriter
    {
      
        private StreamWriter writer;
        private TextWriter console;
        private Encoding encoding = Encoding.UTF8;
   
        public override Encoding Encoding
        {
            get { return encoding; }
        }
        
         public ConsoleFileOutput(string filePath, TextWriter console,
            Encoding encoding = null)
        {
            if (encoding != null)
            {
                this.encoding = encoding;
            }

            this.console = console;
            this.writer = new StreamWriter(filePath, false, this.encoding);
            this.writer.AutoFlush = true;
        }
       
        public override void Write(string value)
        {
            Console.SetOut(console);
            Console.Write(value);
            Console.SetOut(this);
            this.writer.Write(value);
        }

        public override void WriteLine(string value)
        {
            Console.SetOut(console);
            Console.WriteLine(value);
            this.writer.WriteLine(value);
            Console.SetOut(this);
        }

        public override void Flush()
        {
            this.writer.Flush();
        }

        public override void Close()
        {
            this.writer.Close();
        }


        public void Dispose()
        {
            this.writer.Flush();
            this.writer.Close();
            this.writer.Dispose();
            base.Dispose();
        }

    }
}