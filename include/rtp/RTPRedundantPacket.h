/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RTPRedundantPacket.h
 * Author: Sergio
 *
 * Created on 3 de febrero de 2017, 11:58
 */

#ifndef RTPREDUNDANTPACKET_H
#define RTPREDUNDANTPACKET_H



class RTPRedundantPacket:
	public RTPTimedPacket
{
public:
	RTPRedundantPacket(MediaFrame::Type media,BYTE *data,DWORD size);

	BYTE* GetPrimaryPayloadData() 		const { return primaryData;	}
	DWORD GetPrimaryPayloadSize()		const { return primarySize;	}
	BYTE  GetPrimaryType()			const { return primaryType;	}
	BYTE  GetPrimaryCodec()			const { return primaryCodec;	}
	void  SetPrimaryCodec(BYTE codec)	      { primaryCodec = codec;	}

	RTPTimedPacket* CreatePrimaryPacket();

	BYTE  GetRedundantCount()		const { return headers.size();	}
	BYTE* GetRedundantPayloadData(int i)	const { return i<headers.size()?redundantData+headers[i].ini:NULL;	}
	DWORD GetRedundantPayloadSize(int i) 	const { return i<headers.size()?headers[i].size:0;			}
	BYTE  GetRedundantType(int i)		const { return i<headers.size()?headers[i].type:0;			}
	BYTE  GetRedundantCodec(int i)		const { return i<headers.size()?headers[i].codec:0;			}
	BYTE  GetRedundantOffser(int i)		const { return i<headers.size()?headers[i].offset:0;			}
	BYTE  GetRedundantTimestamp(int i)	const { return i<headers.size()?GetTimestamp()-headers[i].offset:0;	}
	void  SetRedundantCodec(int i,BYTE codec)     { if (i<headers.size()) headers[i].codec = codec;			}

private:
	struct RedHeader
	{
		BYTE  type;
		BYTE  codec;
		DWORD offset;
		DWORD ini;
		DWORD size;
		RedHeader(BYTE type,DWORD offset,DWORD ini,DWORD size)
		{
			this->codec = type;
			this->type = type;
			this->offset = offset;
			this->ini = ini;
			this->size = size;
		}
	};
private:
	std::vector<RedHeader> headers;
	BYTE	primaryType;
	BYTE	primaryCodec;
	DWORD	primarySize;
	BYTE*	primaryData;
	BYTE*	redundantData;
};



#endif /* RTPREDUNDANTPACKET_H */
