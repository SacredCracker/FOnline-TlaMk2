using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AuctionAdminMK2.Fonline
{
    public class FOProtoItem
    {
        public int ProtoId { get; set; }
        public string ProtoName { get; set; }
        public string ProtoDescription { get; set; }
        public string Alias { get; set; }
        public int Type { get; set; }

        public void Export(data.dsMain.tItemTypeDataTable typesTable)
        {
            long type = 0;
            var q = typesTable.Where(r => r.FOTypeId == Type);
            if (q.Count() > 0)
                type = q.First().TypeId;
            data.dsMainTableAdapters.TableAdapterManager ta = new AuctionAdminMK2.data.dsMainTableAdapters.TableAdapterManager();
            ta.Init();
            ta.Connection.Open();
            ta.tItemProtoTableAdapter.Insert(ProtoId, ProtoName, ProtoDescription, Alias, type );
            int newId = (int)(ta.tItemProtoTableAdapter.GetLastInsertedId());
            ta.tLotsTableAdapter.UpdateLotsNewProto(newId, ProtoId);
            ta.tItemProtoTableAdapter.DeleteByPidFiltered(ProtoId, newId);
            ta.Connection.Close();
        }
    }
}
