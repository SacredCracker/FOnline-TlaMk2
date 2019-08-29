using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;

namespace AuctionAdminMK2.Fonline
{
    public class FOProtoItemManager
    {
        #region Regex
        // *.fopro
        private const string PidRegex = @"(^ProtoId\=|Pid\=+)(?<pid>[0-9]+)";
        private const string TypRegex = @"\s+(^Type\=+)(?<type>[0-9]+)";
        private const string ProtoRegex =
                @"(^\[Proto\]\s+)"
            +   PidRegex
            +   TypRegex ;
        // *.lst
        private const string lstIdRegex = @"(?<id>[0-9]+)";
        private const string lstNameRegex = @"(?<value>[_a-zA-Z0-9]+)";
        private const string lstItemRegex =
            @"^" + lstIdRegex + @"\s+" + lstNameRegex;
        // *.msg
        private const string MsgEntryRegex = @"^{(?<id>[0-9]+)}{}{(?<value>[^}]*)}";

        #endregion
                
        private List<Fonline.MsgEntry> FOItemAliases = new List<AuctionAdminMK2.Fonline.MsgEntry>();
        private List<Fonline.MsgEntry> FOItemTexts = new List<AuctionAdminMK2.Fonline.MsgEntry>();
        private List<Fonline.MsgEntry> FOItemTextsEngl = new List<AuctionAdminMK2.Fonline.MsgEntry>();

        public List<FOProtoItem> Items = new List<FOProtoItem>();


        public void Load(string path)
        {
            System.IO.FileInfo fiProto = new FileInfo(path);
            System.IO.DirectoryInfo diSrv = fiProto.Directory.Parent.Parent;
            System.IO.DirectoryInfo di;
            System.IO.FileInfo fi;
            if (FOItemAliases.Count() == 0)
            {
                di = diSrv.GetDirectories("data").First();
                fi = di.GetFiles("ItemNames.lst").First();
                using (var msgReader = new AuctionAdminMK2.Fonline.MsgReader(fi.FullName))
                {
                    Fonline.MsgEntry msgEntry = msgReader.ReadNextEntry(lstItemRegex);
                    while (msgEntry != null)
                    {
                        FOItemAliases.Add(msgEntry);
                        msgEntry = msgReader.ReadNextEntry(lstItemRegex);
                    }
                }
            }
            //engl
            if (FOItemTextsEngl.Count() == 0)
            {
                di = diSrv.GetDirectories("text").First().GetDirectories("engl").First();
                fi = di.GetFiles("FOOBJ.MSG").First();
                using (var msgReader = new AuctionAdminMK2.Fonline.MsgReader(fi.FullName ))
                {
                    Fonline.MsgEntry msgEntry = msgReader.ReadNextEntry(MsgEntryRegex);
                    while (msgEntry != null)
                    {
    
                        FOItemTextsEngl.Add(msgEntry);
                        msgEntry = msgReader.ReadNextEntry(MsgEntryRegex);
                    }
                }
               
            }
            // russ
            if (FOItemTexts.Count() == 0)
            {
                di = diSrv.GetDirectories("text").First().GetDirectories("russ").First();
                fi = di.GetFiles("FOOBJ.MSG").First();
                using (var msgReader = new AuctionAdminMK2.Fonline.MsgReader(fi.FullName ))
                {
                    Fonline.MsgEntry msgEntry = msgReader.ReadNextEntry(MsgEntryRegex);
                    while (msgEntry != null)
                    {
                        FOItemTexts.Add(msgEntry);
                        msgEntry = msgReader.ReadNextEntry(MsgEntryRegex);
                    }
                }
               
            }

            string text = string.Empty;
            using (var sr = new StreamReader(path, Encoding.Default))
            {
                text = sr.ReadToEnd();
            }
            var options =
                RegexOptions.Compiled |
                RegexOptions.Multiline; // to handle line beginnings
            Items.Clear();
            var regex = new Regex(ProtoRegex, options);
            var match = regex.Match(text);
           
            while (match.Success)
            {
                Items.Add(ProcessMatch(match));
                match =  match.NextMatch();
            }
        }


        private FOProtoItem ProcessMatch(Match match)
        {
            FOProtoItem proto = new FOProtoItem();
            proto.ProtoId = int.Parse(match.Groups["pid"].Value);
            proto.Type = int.Parse(match.Groups["type"].Value);

            var qName = FOItemTexts.Where(t => t.Id == proto.ProtoId * 100);
            if (qName.Count() > 0)
            {
                proto.ProtoName = qName.First().Text;
            }
            var eName = FOItemTextsEngl.Where(t => t.Id == proto.ProtoId * 100);
            if (eName.Count() > 0)
            {
                proto.ProtoName += "  " + eName.First().Text;
            }
            var qDescr = FOItemTexts.Where(t => t.Id == (proto.ProtoId * 100+1));
            if(qDescr.Count()>0)
                proto.ProtoDescription = qDescr.First().Text;
            var qAlias = FOItemAliases.Where(t => t.Id == proto.ProtoId);
            if (qAlias.Count() > 0)
                proto.Alias = qAlias.First().Text ;

            return proto;
        }
    }
}
