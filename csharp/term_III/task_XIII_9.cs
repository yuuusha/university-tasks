using System;
using System.Diagnostics;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;

namespace Task
{
    class Program
    {
        static string nice_word_pattern = @"(^[a-zA-Z]$)|(^[a-zA-Z])([a-z]+$)|(^[a-zA-Z])([a-z]+)-([a-z]+$)|(^[A-Z]+$)";
        //слово может начинаться с заглавной буквы и состоять из 1 или больше символов
        //слово может быть двойным и начинаться с заглавной
        //слово может быть аббревиатурой

        static string nice_sentence_start_pattern = @"(^[A-Z])|(^[A-Z])(\w)+";
        //static string nice_sentence_end_pattern = @"(\w)+(([.]{3})|([.|!|?]{1})$)";
        //предложение должно начинаться с заглавной буквы
        //предложение может оканчиваться точкой, многоточием, восклицанием, вопросом

        static Regex nice_word = new Regex(nice_word_pattern);
        static Regex nice_sentence_start = new Regex(nice_sentence_start_pattern);
        //static Regex nice_sentence_end = new Regex(nice_sentence_end_pattern);

        static string[] separators = { " ", ", ", "; ", "- ", ", - " };
        static string[] ends = { ". ", "... ", "! ", "? " };

        static bool isNiceText(string text)
        {
            string[] sentence = text.Split(ends, StringSplitOptions.RemoveEmptyEntries);

            foreach (var x in sentence)
            {
                if (!isNiceSentence(x))
                    return false;

                string[] words = x.Split(separators, StringSplitOptions.RemoveEmptyEntries);

                foreach (var y in words)
                {
                    if (!isNiceWord(y))
                        return false;
                }
            }

            return true;
        }
        static bool isNiceSentence(string text)
        {
            if (!(nice_sentence_start.IsMatch(text)))
                return false;

            return true;
        }
        static bool isNiceWord(string word)
        {
            return (nice_word.IsMatch(word));
        }

        static void Main(string[] args)
        {
            using (StreamReader IN = new StreamReader("C:/Users/jojom/source/repos/ConsoleApp1/ConsoleApp1/input13.txt", Encoding.GetEncoding(1251)))
            {
                string text = IN.ReadToEnd();
                Console.WriteLine(isNiceText(text));
                //string[] sentence = text.Split(ends, StringSplitOptions.RemoveEmptyEntries);

                //foreach (var x in sentence)
                //{
                //    Console.WriteLine(x);
                //    Console.WriteLine(isNiceSentence(x));
                //    Console.WriteLine(nice_sentence_start.IsMatch(x));
                //}


                //string[] separators = { " ", ", ", "; ", " - ", ", - " };
                //string[] words = s.Split(separators, StringSplitOptions.None);

                //foreach (var x in words)
                //{
                //    Console.WriteLine("/{0}/", x);
                //    Console.WriteLine(r.IsMatch(x));
                //}


            }
        }
    }
}
