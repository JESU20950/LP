/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 *
 *   antlr -gt practica.g
 *
 */

#define ANTLR_VERSION	13333
#include "pcctscfg.h"
#include "pccts_stdio.h"

#include <string>
#include <iostream>
#include <map>
using namespace std;

// struct to store information about tokens
typedef struct {
  string kind;
  string text;
} Attrib;

// function to fill token information (predeclaration)
void zzcr_attr(Attrib *attr, int type, char *text);

// fields for AST nodes
#define AST_FIELDS string kind; string text;
#include "ast.h"

// macro to create a new AST node (and function predeclaration)
#define zzcr_ast(as,attr,ttype,textt) as=createASTnode(attr,ttype,textt)
AST* createASTnode(Attrib* attr, int ttype, char *textt);
#define GENAST

#include "ast.h"

#define zzSET_SIZE 4
#include "antlr.h"
#include "tokens.h"
#include "dlgdef.h"
#include "mode.h"

/* MR23 In order to remove calls to PURIFY use the antlr -nopurify option */

#ifndef PCCTS_PURIFY
#define PCCTS_PURIFY(r,s) memset((char *) &(r),'\0',(s));
#endif

#include "ast.c"
zzASTgvars

ANTLR_INFO

#include <cstdlib>
#include <cmath>

int seed;
string user;
string bot;   
AST *root;
string auxiliar;//Guarda los datos de entrada

// function to fill token information
void zzcr_attr(Attrib *attr, int type, char *text) {
  
    attr->kind = text;
  attr->text = "";
}

//function to create a new AST list
AST* createASTlist(AST* n){
  AST *as=new AST;
  as->kind="list";
  as->right=NULL;
  as->down=n;
  return as;
}

// function to create a new AST node
AST* createASTnode(Attrib* attr, int type, char* text) {
  AST* as = new AST;
  as->kind = attr->kind; 
  as->text = attr->text;
  as->right = NULL; 
  as->down = NULL;
  return as;
}

/// get nth child of a tree. Count starts at 0.
/// if no such child, returns NULL
AST* child(AST *a,int n) {
  AST *c=a->down;
  for (int i=0; c!=NULL && i<n; i++) c=c->right;
  return c;
} 

/// print AST, recursively, with indentation
void ASTPrintIndent(AST *a,string s)
{
  if (a==NULL) return;
  
  cout<<a->kind;
  if (a->text!="") cout<<"("<<a->text<<")";
  cout<<endl;
  
  AST *i = a->down;
  while (i!=NULL && i->right!=NULL) {
    cout<<s+"  \\__";
    ASTPrintIndent(i,s+"  |"+string(i->kind.size()+i->text.size(),' '));
    i=i->right;
  }
  
  if (i!=NULL) {
    cout<<s+"  \\__";
    ASTPrintIndent(i,s+"   "+string(i->kind.size()+i->text.size(),' '));
    i=i->right;
  }
}

void imp_pregunta(AST *a, string nombre){
  if(a->down == NULL){
    cout << bot << " > " << user << ", ";
    while(a!=NULL){
      cout << a->kind << " ";
      a=a->right;
    }
    cout << "?" << endl;
  }else{
    while(a!=NULL){
      cout << a->kind << ":";
      AST *orden  = a->down->down;
      while(orden!=NULL){
        cout << " " << orden->kind;
        orden = orden->right;
      }
      cout << endl;            
      a = a->right;
    }
    cout << user << " > ";
    cin >> auxiliar;    
  }
}

void buscador(string nombre){
  AST *a = root->down->down;
  while(a != NULL){
    if(a->kind == nombre){
      if(a->down->kind == "->"){
        buscador(a->down->down->kind);
        buscador(a->down->down->right->kind);
      }else{
        imp_pregunta(a->down->down, nombre);
      }
    }
    a = a->right;
  }
}

int contador(AST *a){ 
  int i=0;    
  AST *aux=a->down;
  while(aux!=NULL){
    i++;
    aux=aux->right;
  }
  return i;
}

//Busca el bot en el arbol
void dobot(string nombre){
  bot = nombre;
  cout << bot << " > WHAT IS YOUR NAME ? " << endl; 
  cin >> user;
  AST *a = root->down->right->down;
  while(a != NULL){
    if(a->kind == nombre){
      AST *orden = a->down->down;
      while(orden!=NULL){
        if(orden->kind == "OR"){
          int opciones = contador(orden);
          srand(seed);//Aqui se determina el seed, cambiar para probar distintos seeds                    
          AST *aux = orden->down;
          opciones = rand()%opciones;                    
          for(int i=0;i<opciones;i++){ aux = aux->right;}                    
          buscador(aux->kind);
        }else{
          buscador(orden->kind);
        }            
        orden= orden->right;
      }
    }
    a = a->right;
  }
  cout << bot << " > THANKS FOR THE CHAT "<< user <<"!" << endl;
}

void evaluate() {
  AST *a = root->down->right->right->down;
  seed = atoi(a->kind.c_str());
  a = a->right;
  while(a != NULL){
    dobot(a->kind);
    a = a->right;
  }
}




/// print AST 
void ASTPrint(AST *a)
{
  while (a!=NULL) {
    cout<<" ";
    ASTPrintIndent(a,"");
    a=a->right;
  }
}

int main() {
  root = NULL;
  ANTLR(chatbot(&root), stdin);
  ASTPrint(root);
  evaluate();
}

void
#ifdef __USE_PROTOS
chatbot(AST**_root)
#else
chatbot(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  conversations(zzSTR); zzlink(_root, &_sibling, &_tail);
  chats(zzSTR); zzlink(_root, &_sibling, &_tail);
  startchat(zzSTR); zzlink(_root, &_sibling, &_tail);
  (*_root)=createASTlist(_sibling);
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x1);
  }
}

void
#ifdef __USE_PROTOS
conversations(AST**_root)
#else
conversations(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (LA(1)==TEXT) ) {
      initconv(zzSTR); zzlink(_root, &_sibling, &_tail);
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  (*_root)=createASTlist(_sibling);
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x2);
  }
}

void
#ifdef __USE_PROTOS
chats(AST**_root)
#else
chats(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (LA(1)==CBOT) ) {
      initchat(zzSTR); zzlink(_root, &_sibling, &_tail);
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  (*_root)=createASTlist(_sibling);
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x4);
  }
}

void
#ifdef __USE_PROTOS
startchat(AST**_root)
#else
startchat(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (LA(1)==INTERACTION) ) {
      start(zzSTR); zzlink(_root, &_sibling, &_tail);
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  (*_root)=createASTlist(_sibling);
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x8);
  }
}

void
#ifdef __USE_PROTOS
initconv(AST**_root)
#else
initconv(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(TEXT); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(ASIG);  zzCONSUME;
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    if ( (LA(1)==CONV) ) {
      zzmatch(CONV);  zzCONSUME;
      con(zzSTR); zzlink(_root, &_sibling, &_tail);
    }
    else {
      if ( (setwd1[LA(1)]&0x10) ) {
        respuesta(zzSTR); zzlink(_root, &_sibling, &_tail);
      }
      else {zzFAIL(1,zzerr1,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp2);
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x20);
  }
}

void
#ifdef __USE_PROTOS
respuesta(AST**_root)
#else
respuesta(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    if ( (LA(1)==QUES) ) {
      zzmatch(QUES);  zzCONSUME;
      preg(zzSTR); zzlink(_root, &_sibling, &_tail);
    }
    else {
      if ( (LA(1)==ANS) ) {
        zzmatch(ANS);  zzCONSUME;
        {
          zzBLOCK(zztasp3);
          zzMake0;
          {
          if ( (setwd1[LA(1)]&0x40) ) {
            {
              zzBLOCK(zztasp4);
              zzMake0;
              {
              while ( (LA(1)==NUM) ) {
                res1(zzSTR); zzlink(_root, &_sibling, &_tail);
                zzLOOP(zztasp4);
              }
              zzEXIT(zztasp4);
              }
            }
          }
          else {
            if ( (LA(1)==LCOR) ) {
              res2(zzSTR); zzlink(_root, &_sibling, &_tail);
            }
            else {zzFAIL(1,zzerr2,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
          zzEXIT(zztasp3);
          }
        }
      }
      else {zzFAIL(1,zzerr3,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp2);
    }
  }
  (*_root)=createASTlist(_sibling);
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x80);
  }
}

void
#ifdef __USE_PROTOS
preg(AST**_root)
#else
preg(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (LA(1)==TEXT) ) {
      zzmatch(TEXT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  zzmatch(EQUES);  zzCONSUME;
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x1);
  }
}

void
#ifdef __USE_PROTOS
res1(AST**_root)
#else
res1(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(NUM); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(ASIG);  zzCONSUME;
  opc1(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x2);
  }
}

void
#ifdef __USE_PROTOS
opc1(AST**_root)
#else
opc1(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (LA(1)==TEXT) ) {
      zzmatch(TEXT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  zzmatch(EANS); 
  (*_root)=createASTlist(_sibling);
 zzCONSUME;

  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x4);
  }
}

void
#ifdef __USE_PROTOS
res2(AST**_root)
#else
res2(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(LCOR);  zzCONSUME;
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    {
      zzBLOCK(zztasp3);
      zzMake0;
      {
      for (;;) {
        if ( !((setwd2[LA(1)]&0x8))) break;
        if ( (LA(1)==LPAREN) ) {
          zzmatch(LPAREN);  zzCONSUME;
          resaux(zzSTR); zzlink(_root, &_sibling, &_tail);
        }
        else {
          if ( (LA(1)==COMA) ) {
            zzmatch(COMA);  zzCONSUME;
          }
          else break; /* MR6 code for exiting loop "for sure" */
        }
        zzLOOP(zztasp3);
      }
      zzEXIT(zztasp3);
      }
    }
    zzmatch(RCOR);  zzCONSUME;
    zzEXIT(zztasp2);
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x10);
  }
}

void
#ifdef __USE_PROTOS
resaux(AST**_root)
#else
resaux(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(NUM); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(COMA);  zzCONSUME;
  opc2(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x20);
  }
}

void
#ifdef __USE_PROTOS
opc2(AST**_root)
#else
opc2(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (LA(1)==TEXT) ) {
      zzmatch(TEXT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  zzmatch(RPAREN); 
  (*_root)=createASTlist(_sibling);
 zzCONSUME;

  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x40);
  }
}

void
#ifdef __USE_PROTOS
con(AST**_root)
#else
con(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(SELID);  zzCONSUME;
  zzmatch(TEXT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(LINK); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(SELID);  zzCONSUME;
  zzmatch(TEXT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x80);
  }
}

void
#ifdef __USE_PROTOS
initchat(AST**_root)
#else
initchat(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(CBOT);  zzCONSUME;
  zzmatch(TEXT); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(ASIG);  zzCONSUME;
  conex(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd3, 0x1);
  }
}

void
#ifdef __USE_PROTOS
conex(AST**_root)
#else
conex(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(SELID);  zzCONSUME;
  zzmatch(TEXT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(THEN); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    if ( (LA(1)==LPAREN) ) {
      ors1(zzSTR); zzlink(_root, &_sibling, &_tail);
    }
    else {
      if ( (LA(1)==SELID) ) {
        ors2(zzSTR); zzlink(_root, &_sibling, &_tail);
      }
      else {zzFAIL(1,zzerr4,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp2);
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd3, 0x2);
  }
}

void
#ifdef __USE_PROTOS
ors1(AST**_root)
#else
ors1(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(LPAREN);  zzCONSUME;
  zzmatch(SELID);  zzCONSUME;
  zzmatch(TEXT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(OR); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(SELID);  zzCONSUME;
  zzmatch(TEXT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    for (;;) {
      if ( !((setwd3[LA(1)]&0x4))) break;
      if ( (LA(1)==OR) ) {
        zzmatch(OR);  zzCONSUME;
        zzmatch(SELID);  zzCONSUME;
        zzmatch(TEXT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
      }
      else {
        if ( (LA(1)==RPAREN) ) {
          zzmatch(RPAREN);  zzCONSUME;
        }
        else break; /* MR6 code for exiting loop "for sure" */
      }
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd3, 0x8);
  }
}

void
#ifdef __USE_PROTOS
ors2(AST**_root)
#else
ors2(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(SELID);  zzCONSUME;
  zzmatch(TEXT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(OR); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(SELID);  zzCONSUME;
  zzmatch(TEXT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd3, 0x10);
  }
}

void
#ifdef __USE_PROTOS
start(AST**_root)
#else
start(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(INTERACTION);  zzCONSUME;
  zzmatch(NUM); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (LA(1)==TEXT) ) {
      zzmatch(TEXT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  zzmatch(END);  zzCONSUME;
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd3, 0x20);
  }
}
