from vsip import *
import vsiputils as vsip
class JVSIP (object):
    init = 0
    def __init__(self):
        if JVSIP.init:
            self.vsipInit=0;
            JVSIP.init +=1;
        else:
            self.vsipInit = vsip.init()
            if self.vsipInit:
                printf('VSIP failed to initialize')
            else:
                JVSIP.init = 1;
 
    def __del__(self):
        JVSIP.init -= 1
        if JVSIP.init == 0:
            vsip.finalize()

class Block (object):
    blockTypes = ['block_f','block_d','cblock_f','cblock_d',
              'block_vi','block_mi','block_bl',
              'block_si','block_i','block_uc']
    derivedTypes = ['real_f','real_d']
    matrixTypes=['mview_f','mview_d','cmview_f','cmview_d',
                 'mview_si','mview_i','mview_uc','mview_bl']
    vectorTypes=['vview_f','vview_d','cvview_f','cvview_d',
                 'vview_si','vview_i','vview_uc',
                 'vview_mi', 'vview_vi','vview_bl']
    complexTypes=['cvview_f','cmview_f','cvview_d','cmview_d','cblock_f','cblock_d']
    #View Class defined here
    class __View(object):
        viewTypes=['mview_f','mview_d','cmview_f','cmview_d',
                 'mview_si','mview_i','mview_uc','mview_bl',
                 'vview_f','vview_d','cvview_f','cvview_d',
                 'vview_si','vview_i','vview_uc',
                 'vview_mi', 'vview_vi','vview_bl']
        def __init__(self,view,block):
            self.__jvsip = JVSIP()
            self.__vsipView = view
            self.__pyBlock   = block
            self.__type      =vsip.getType(view)[1]
            self.__major     ='COL'
        def __del__(self):
            del(self.__pyBlock)
            del(self.__jvsip)
            vsip.destroy(self.__vsipView)
        # Support functions
        @classmethod
        def supported(cls):
            return cls.viewTypes
        def compactAttrib(self,b):
            """Function used for introspection of view objects. Output useful for creating
               attributes needed for creation of new views based on existing views.
               usage:
                 attr=compactAttrib(b)
                 attr is a tuple with three entries.
                 attr[0] is the block type of self if b is 0 (see below for b is 1).
                 attr[1] is len(self)
                 attr[2] is an attribute (tuple) suitable for entry into bind.
               NOTE:
               if b is 1 (not 0) and self.block.type is real then attr[0] will be complex
               if b is 1 and self.block.type is complex then attr[0] will be real
               if self.block.type is not in Block.complexTypes then b is treated as 0
                 and the actual value passed in is ignored
            """
            tdict={'block_f':'cblock_f','block_d':'cblock_d',
                   'cblock_f':'block_f','cblock_d':'block_d'}
            t = self.block.type
            if t in Block.complexTypes and b != 0:
                t=tdict[t]
            length = len(self)
            if self.type in Block.vectorTypes:
                attr=(0,1,length)
            elif self.type in Block.matrixTypes:
                size=vsip.size(self.view)
                if size[1] < size[3]:
                    attr=(0,1,size[2],size[2],size[4])
                else:
                    attr=(0,size[4],size[2],1,size[4])
            else:
                print('Type <:' + self.type + ':> not supported for compactAttrib')
                return False
            return (t,length,attr)
        @property
        def copy(self):
            """For vector or matrix A then
               B = A.copy will create a compact view B which is a copy
               of A. Note compact means the view exactly fits in the Block
               with unit stride in the major direction. The block is new
               and not the same block associated with A.
               This is an easy way to create a new data space for out of place
               operations.
               For instance B = A.copy.sin will leave A alone, copy its elements to
               new view (and block) B and then do an in-place sine operation on B.
            """
            attr=self.compactAttrib(0)
            b = self.block.otherBlock(attr[0],attr[1])
            newView = b.bind(attr[2])
            vsip.copy(self.view,newView.view)
            return newView
        @property
        def clone(self):
            return self.__clone(self)   
        #data generators
        def ramp(self,start,increment):
            supported = ['vview_f','vview_d','vview_i','vview_si','vview_uc','vview_vi']
            if self.type in supported:
                vsip.ramp(start,increment,self.__vsipView)
                return self
            else:
                print('Type <:'+self.type+':> not supported for ramp')
                return False
        def fill(self,aScalar):
            vsip.fill(aScalar,self.view)
            return self
        #support functions
        def subview(self,(atuple)):
            """usage:
               given view aView then
                  anotherView = aView.sub(aTuple)
               where:
                  aTuple is (index, stride, length) for a vector
                  aTuple is ((rowindex,colindex), colstride, collength, rowstride, rowlength) for a matrix
               anotherView is a view on the same block and data as aView. 
               Offset, strides and lengths are defined on aView, not the block.
            """
            attr = vsip.getattrib(self.view)
            retval=self.clone
            if 'vview' in self.type and 'vattr' in vsip.getType(attr)[1]:
                offset = atuple[0] * attr.stride + attr.offset
                stride = attr.stride * atuple[1]
                length = atuple[2]
                return self.block.bind((offset,stride,length))
            elif 'mview' in self.type and 'mattr' in vsip.getType(attr)[1]:
                offset = atuple[0][0] * attr.col_stride + atuple[0][1] * attr.row_stride + attr.offset
                rowstride = attr.row_stride * atuple[3]
                colstride = attr.col_stride * atuple[1]
                rowlength = atuple[4]
                collength = atuple[2]
                return self.block.bind((offset,colstride,collength,rowstride,rowlength))
            else:
                print('object not supported for subview')
                return False
        @property
        def attrib(self):
            attr=vsip.getattrib(self.view)
            if 'vview' in self.type:
                return {'offset':attr.offset,'stride':attr.stride,'length':attr.length}
            elif 'mview' in self.type:
                return {'offset':attr.offset,
                        'colstride':attr.col_stride,'collength':attr.col_length,
                        'rowstride':attr.row_stride,'rowlength':attr.row_length}
            else:
                print('Object type not supported for attrib')
                return False
        def putattrib(self,attrib):
            if 'mview' in self.type:
                if 'collength' in attrib:
                    attr=vsip.getattrib(self.view)
                    attr.offset = attrib['offset']
                    attr.row_length = attrib['rowlength']
                    attr.col_length = attrib['collength']
                    attr.row_stride = attrib['rowstride']
                    attr.col_stride = attrib['rowstride']
                    vsip.putattrib(self.view,attr)
                    return self
                else:
                    print('Input attribute does not appear to be for a matrix')
                    return False
            elif 'vview' in self.type:
                if 'length' in attrib:
                    attr=vsip.getattrib(self.view)
                    attr.offset = attrib['offset']
                    attr.stride = attrib['stride']
                    attr.length = attrib['length']
                    vsip.putattrib(self.view,attr)
                    return self
                else:
                    print('Input attribute does not appear to be for a vector')
                    return False
            else:
                print('Type must be a matrix or vector')
                return False
        @property
        def view(self):
            return self.__vsipView
        @property
        def compact(self):
            if self.type in Block.vectorTypes:
                if self.stride == 1:
                    return True
                else:
                    return False
            elif self.type in Block.matrixTypes:
                attrib=self.attrib
                if attrib['colstride'] == 1 and attrib['rowstride'] == attrib['collength']:
                    return True
                elif attrib['rowstride'] == 1 and attrib['colstride'] == attrib['rowlength']:
                    return True
                else:
                    return False
            else:
                print('Type not a matrix or vector view')
                return False
  
        @property
        def major(self):
            """ This is an attribute that is used to determine certain functionality.
                The major attribue does NOT necessarily agree with the smallest stride direction.
            """
            return self.__major
        def setMajor(self,major):
            self.__major = major
        @property
        def real(self):
            return self.realview.copy
        @property
        def imag(self):
            return self.imagview.copy
        def colview(self,j):
            if self.type in Block.matrixTypes:
                v = vsip.colview(self.view,j)
                return self.__newView(v,self.block)
            else:
                print('view not a matrix type')
                return False
        def rowview(self,i):
            if self.type in Block.matrixTypes:
                v=vsip.rowview(self.view,i)
                return self.__newView(v,self.block)
            else:
                print('view not a matrix type')
                return False
        def diagview(self,i):
            if self.type in Block.matrixTypes:
                v = vsip.diagview(self.view,i)
                return self.__newView(v,self.block)
        @property
        def transview(self):
            if 'mview' in self.type:
                return self.__newView(vsip.transview(self.view),self.block)
            else:
                print('Method transview only works on matrix views')
                return False
        @classmethod
        def __newView(cls,v,b):
            return cls(v,b)         
        @property
        def realview(self):
            return self.__realview(self)
        @property
        def imagview(self):
            return self.__imagview(self)
        @classmethod
        def __realview(cls,V):
            views={'vview_f':'real_f', 'vview_d':'real_d',
                   'mview_f':'real_f','mview_d':'real_d'}
            v=vsip.realview(V.view)
            t=views[vsip.getType(v)[1]]
            B=V.block
            l=B.length
            b=vsip.getblock(v)
            newB = B.otherBlock(t,(b,l))
            return cls(v,newB)
        @classmethod
        def __imagview(cls,V):
            views={'vview_f':'real_f', 'vview_d':'real_d',
                   'mview_f':'real_f','mview_d':'real_d'}
            v=vsip.imagview(V.view)
            t=views[vsip.getType(v)[1]]
            B=V.block
            l=B.length
            b=vsip.getblock(v)
            newB = B.otherBlock(t,(b,l))
            return cls(v,newB)
        #view attributes
        @property
        def offset(self):
            return vsip.getoffset(self.view)
        def putoffset(self,o):
            vsip.putoffset(self.view,o)
            return self
        @property
        def length(self):
            if self.type in Block.vectorTypes:
                return vsip.getlength(self.view)
            elif self.type in Block.matrixTypes:
                print('View not a vector type')
                return False
            else:
                print('Object not of the proper type')
                return False
        def putlength(self,length):
            if self.type in Block.vectorTypes:
                vsip.putlength(self.view,length)
                return self
            elif self.type in Block.matrixTypes:
                print('View not a vector type')
                return False
            else:
                print('Object not of the proper type')
                return False
        @property
        def stride(self):
            if self.type in Block.vectorTypes:
                return vsip.getstride(self.view)
            elif self.type in Block.matrixTypes:
                print('View not a vector type')
                return False
            else:
                print('Object not of the proper type')
                return False
        def putstride(self,stride):
            if self.type in Block.vectorTypes:
                vsip.putstride(self.view,stride)
                return self
            elif self.type in Block.matrixTypes:
                print('View not a vector type')
                return False
            else:
                print('Object not of the proper type')
                return False
        @property
        def rowlength(self):
            if self.type in Block.vectorTypes:
                print('View not a matrix type')
                return False
            elif self.type in Block.matrixTypes:
                return vsip.getrowlength(self.view)
            else:
                print('Object not of the proper type')
                return False
        def putrowlength(self,length):
            if self.type in Block.vectorTypes:
                print('View not a matrix type')
                return False
            elif self.type in Block.matrixTypes:
                vsip.putrowlength(self.view,length)
                return self
            else:
                print('Object not of the proper type')
                return False
        @property
        def collength(self):
            if self.type in Block.vectorTypes:
                print('View not a matrix type')
                return False
            elif self.type in Block.matrixTypes:
                return vsip.getcollength(self.view)
            else:
                print('Object not of the proper type')
                return False
        def putcollength(self,length):
            if self.type in Block.vectorTypes:
                print('View not a matrix type')
                return False
            elif self.type in Block.matrixTypes:
                vsip.putcollength(self.view,length)
                return self
            else:
                print('Object not of the proper type')
                return False
        @property
        def rowstride(self):
            if self.type in Block.vectorTypes:
                print('View not a matrix type')
                return False
            elif self.type in Block.matrixTypes:
                return vsip.getrowstride(self.view)
            else:
                print('Object not of the proper type')
                return False
        def putrowstride(self,stride):
            if self.type in Block.vectorTypes:
                print('View not a matrix type')
                return False
            elif self.type in Block.matrixTypes:
                vsip.putrowstride(self.view,stride)
                return self
            else:
                print('Object not of the proper type')
                return False
        @property
        def colstride(self):
            if self.type in Block.vectorTypes:
                print('View not a matrix type')
                return False
            elif self.type in Block.matrixTypes:
                return vsip.getcolstride(self.view)
            else:
                print('Object not of the proper type')
                return False
        def putcolstride(self,stride):
            if self.type in Block.vectorTypes:
                print('View not a matrix type')
                return False
            elif self.type in Block.matrixTypes:
                vsip.putcolstride(self.view,stride)
                return self
            else:
                print('Object not of the proper type')
                return False
        @property
        def block(self):
            return self.__pyBlock
        @property
        def type(self):
            return self.__type
        @classmethod
        def __clone(cls,V):
            v=vsip.cloneview(V.view)
            b=V.block
            return cls(v,b)
        @property
        def list(self):
            if self.type in Block.vectorTypes:
                return vsip.vList(self.view)
            elif self.type in Block.matrixTypes:
                return vsip.mList(self.view)
            else:
                print('Type not a matrix or vector')
                return False
        @property
        def mcopy_to_list(self):
            return vsip.mList(self.__vsipView)
        def __getitem__(self,i):
            val=vsip.get(self.view,i)
            if 'cscalar' in repr(val):
                c=complex(val.r,val.i)
                return c
            else:
                return val
        def __setitem__(self,i,value):
            return vsip.put(self.__vsipView,i,value)
        def __len__(self):
            attr=vsip.size(self.__vsipView)
            n = attr[2]
            if len(attr) > 3:
                n *= attr[4]
            return n
        # window functions
        def cheby(self,ripple):
            t=vsip.getType(self.view)[1]
            f={'vview_f':vsip_vcreate_cheby_f,
               'vview_d':vsip_vcreate_cheby_d}
            if f.has_key(t):
                v=f[t](vsip.getlength(self.view),ripple,0)
                vsip.copy(v,self.view)
                vsip.allDestroy(v)
                return self
            else:
                print('View type <:' + t +':> does not support function cheby')
        def kaiser(self,beta):
            t=vsip.getType(self.view)[1]
            f={'vview_f':vsip_vcreate_kaiser_f,
               'vview_d':vsip_vcreate_kaiser_d}
            if f.has_key(t):
                v=f[t](vsip.getlength(self.view),beta,0)
                vsip.copy(v,self.view)
                vsip.allDestroy(v)
                return self
            else:
                print('View type <:' + t +':> does not support function kaiser')
        @property
        def blackman(self):
            t=vsip.getType(self.view)[1]
            f={'vview_f':vsip_vcreate_blackman_f,
               'vview_d':vsip_vcreate_blackman_d}
            if f.has_key(t):
                v=f[t](vsip.getlength(self.view),0)
                vsip.copy(v,self.view)
                vsip.allDestroy(v)
                return self
            else:
                print('View type <:' + t +':> does not support property blackman')
        @property
        def hanning(self):
            t=vsip.getType(self.view)[1]
            f={'vview_f':vsip_vcreate_hanning_f,
               'vview_d':vsip_vcreate_hanning_d}
            if f.has_key(t):
                v=f[t](vsip.getlength(self.view),0)
                vsip.copy(v,self.view)
                vsip.allDestroy(v)
                return self
            else:
                print('View type <:' + t +':> does not support property blackman')
        # Elementwise add, sub, mul, div
        def __iadd__(self,other):
            if 'scalar' in vsip.getType(other)[1] :
                vsip.add(other,self.view,self.view)
                return self
            elif 'pyJvsip.__View' in repr(other):
                vsip.add(self.view,other.view,self.view)
                return self
            else:
                print('Object <:' + repr(other) +  ':> not supported for add')
                return False
        def __add__(self,other):
            retval = self.copy
            retval += other
            return retval
        def __radd__(self,other):
            retval = self.copy
            retval += other
            return retval
        def __isub__(self,other): # -=other
            if 'scalar' in vsip.getType(other)[1] : # v-a
                vsip.add(-other,self.view,self.view)
                return self
            elif 'pyJvsip.__View' in repr(other):
                vsip.sub(self.view,other.view,self.view)
                return self
            else:
                print('Object <:' + repr(other) +  ':> not supported for sub')
                return False
        def __sub__(self,other):#self - other
            retval=self.copy
            retval -= other
            return retval
        def __rsub__(self,other): #other - self
            if 'scalar' in vsip.getType(other)[1]:
                retval = self.copy.neg
                vsip.add(other,retval.view,retval.view)
                return retval
            elif 'pyJvsip.__View' in repr(other):
                retval = other.copy
                vsip.sub(retval.view,self.view,retval.view)
                return retval
            else:
                print('Object <:' + repr(other) +  ':> not supported for sub')
                return False
        def __imul__(self,other):# *=other
            if 'scalar' in vsip.getType(other)[1] :
                vsip.mul(other,self.view,self.view)
                return self
            elif 'pyJvsip.__View' in repr(other):
                vsip.mul(other.view,self.view,self.view)
                return self
            else:
                print('Object <:' + repr(other) +  ':> not supported for mul')
                return False
        def __mul__(self,other):
            retval = self.copy
            retval *= other
            return retval
        def __rmul__(self,other):
            if 'scalar' in vsip.getType(other)[1]:
                retval = self.copy
                vsip.mul(other,retval.view,retval.view)
                return retval
            elif 'pyJvsip.__View' in repr(other):
                retval = other.copy
                vsip.mul(retval.view,self.view,retval.view)
                return retval
            else:
                print('Object <:' + repr(other) +  ':> not supported for mul')
                return False
        def __idiv__(self,other):
            if 'scalar' in vsip.getType(other):
                vsip.div(self.view,other,self.view)
                return self
            elif 'pyJvsip.__View' in repr(other):
                vsip.div(self.view,other.view,self.view)
                return self
            else:
                print('Object <:' + repr(other) +  ':> not supported for div')
                return False                 
        def __div__(self,other):
            retval=self.copy
            retval /=other
            return retval
        def __rdiv__(self,other): # other / self
            if 'scalar' in vsip.getType(other):
                print('Divide scalar by view not supported')
                return False
            else:
                retval=other.copy
                vsip.div(retval.view,self.view,retval.view)
                return retval
        # Elementary math functions
        @property
        def acos(self):
            vsip.acos(self.view,self.view)
            return self
        @property
        def asin(self):
            vsip.asin(self.view,self.view)
            return self
        @property
        def cos(self):
            vsip.cos(self.view,self.view)
            return self
        @property
        def cosh(self):
            vsip.cosh(self.view,self.view)
            return self
        @property
        def exp(self):
            vsip.exp(self.view,self.view)
            return self
        @property
        def exp10(self):
            vsip.exp10(self.view,self.view)
            return self
        @property
        def log(self):
            vsip.log(self.view,self.view)
            return self
        @property
        def log10(self):
            vsip.log10(self.view,self.view)
            return self
        @property
        def sin(self):
            vsip.sin(self.view,self.view)
            return self
        @property
        def sinh(self):
            vsip.sinh(self.view,self.view)
            return self
        @property
        def sqrt(self):
            vsip.sqrt(self.view,self.view)
            return self
        @property
        def tan(self):
            vsip.tan(self.view,self.view)
            return self
        @property
        def tanh(self):
            vsip.tanh(self.view,self.view)
            return self
        # Unary Operations
        @property
        def arg(self):
            """ Input vector of type complex
                arg creates and returns a new vector of type real 
            """
            attrs=self.compactAttrib(1)
            out=self.block.otherBlock(attr[0],attr[1]).bind(attr[2])
            vsip.arg(self.view,out.view)
            return out      
        @property
        def conj(self):
            vsip.conj(self.view,self.view)
            return self  
        @property   
        def cumsum(self):
            vsip.cumsum(self.view,self.view)
            return self
        @property
        def euler(self):
            """ Input vector of type real
                arg creates and returns a new vector of type complex 
            """
            attrs=self.compactAttrib(1)
            out=self.block.otherBlock(attr[0],attr[1]).bind(attr[2])
            vsip.euler(self.view,out.view)
            return out      
        def __neg__(self):
            vsip.neg(self.view,self.view)
        @property
        def meansqval(self):
            """ returns scalar value
            """
            return vsip.meansqval(self)
            return self
        @property
        def meanval(self):
            """ returns scalar value
            """
            return vsip.meanval(self.view)
        @property
        def recip(self):
            vsip.recip(self.view,self.view)
            return self
        @property
        def rsqrt(self):
            vsip.rsqrt(self.view,self.view)
            return self
        @property 
        def sq(self):
            vsip.sq(self.view,self.view)
            return self
        @property
        def sumval(self):
            """returns a scalar
            """
            return vsip.sumval(self.view)
        @property
        def sumsqval(input):
            """ returns a scalar
            """
            return sumsqval(self.view)
    #Block specific class below
    def __init__(self,block_type,length):
        other = ['real_f','imag_f','real_d','imag_d']
        self.__jvsip = JVSIP()
        if block_type in Block.blockTypes:
            self.__vsipBlock = vsip.create(block_type,(length,VSIP_MEM_NONE))
            self.__length = length
            self.__type = block_type
        elif block_type in other:
            self.__vsipBlock = length[0]
            self.__length = length[1]
            self.__type = block_type
        else:
            print('block type <:'+block_type+':> not support by Block class')
    def __del__(self):
        if self.__type in Block.blockTypes:
            vsip.destroy(self.__vsipBlock)
        del(self.__jvsip)            
    def bind(self,attr):
        view = vsip.bind(self.__vsipBlock,attr)
        retval = self.__View(view,self)
        retval.setMajor('COL')
        if len(attr) > 3:
            if attr[3] < attr[1]:
                retval.setMajor('ROW')
        return retval
    @classmethod
    def supported(cls):
        return {'blockTypes':Block.blockTypes,'viewTypes':Block.__View.supported()} 
    @property
    def copy(self):
        """ This makes a new block object identical to the calling block object.
            Data in the old block object is NOT copied to the  new block object.
        """
        return self.otherBlock(self.type,self.length)
    @classmethod
    def otherBlock(cls,blk,length):
        """
        This method is used internal to the pyJvsip module.
        It is not intended to be used in user code.
        """
        return cls(blk,length)           
    @property
    def type(self):
        return self.__type
    @property
    def length(self):
        return self.__length
    def __len__(self):
        return self.length

class Rand (object):
    """ 
       Usage
            randObj=Rand(aType,aSeed)
            where aType is one of 'PRNG' or 'NPRNG'
            and aSeed is an integer number
      'PRNG' signifies the portable VSIP version and 'NPRNG' signifies the non-portable
       version.
            randObj.randn(a)
            randObj.randu(a)
       fills view object a with the VSIPL normal or uniform (respectivly) random data.       
    """
    def __init__(self,t,seed):
        self.__jvsip = JVSIP()
        self.__type = t
        self.__seed = seed
        f={'PRNG':'vsip_randcreate(seed,1,1,0)',
           'NPRNG':'vsip_randcreate(seed,1,1,1)'}
        if f.has_key(t):
            self.__rng=eval(f[t])
        else:
            print("type must be either 'PRNG' or 'NPRNG'")

    def __del__(self):
        vsip.destroy(self.__rng)
        del(self.__jvsip)
    @property
    def type(self):
        return self__type;
    @property
    def seed(self):
        return(self.__seed)
    @property
    def nextu(self):
        return vsip_randu_d(self.__rng)
    @property
    def nextn(self):
        return vsip_randn_d(self.__rng)
    @property
    def rng(self):
        return self.__rng
    def randn(self,a):
        t=vsip.getType(a.view)[1]
        f = {'cvview_d':vsip_cvrandn_d,
             'cvview_f':vsip_cvrandn_f,
             'vview_d':vsip_vrandn_d,
             'vview_f':vsip_vrandn_f}
        if f.has_key(t):
            f[t](self.rng,a.view)
            return a
        else:
            print('Not a supported type')
    def randu(self,a):
        t=vsip.getType(a.view)[1]
        f = {'cvview_d':vsip_cvrandu_d,
             'cvview_f':vsip_cvrandu_f,
             'vview_d':vsip_vrandu_d,
             'vview_f':vsip_vrandu_f}
        if f.has_key(t):
            f[t](self.rng,a.view)
            return a
        else:
            print('Not a supported type')

class FFT (object):
    fftTypes = ['ccfftip_f', 'ccfftop_f', 'rcfftop_f', 'crfftop_f', 'ccfftip_d', 
                'ccfftop_d', 'rcfftop_d', 'crfftop_d', 'ccfftmip_f', 'ccfftmop_f', 
                'rcfftmop_f', 'crfftmop_f', 'ccfftmip_d', 'ccfftmop_d', 'rcfftmop_d', 
                 'crfftmop_d']
    fftViewDict = {'ccfftip_d':'cvview_d', 
                   'ccfftip_f':'cvview_f', 
                   'ccfftop_d':'cvview_dcvview_d', 
                   'ccfftop_f':'cvview_fcvview_f', 
                   'rcfftop_d':'vview_dcvview_d', 
                   'rcfftop_f':'vview_fcvview_f', 
                   'crfftop_d':'cvview_dvview_d', 
                   'crfftop_f':'cvview_dvview_f', 
                   'ccfftmip_d':'cmview_d', 
                   'ccfftmip_f':'cmview_f', 
                   'ccfftmop_d':'cmview_dcmview_d', 
                   'ccfftmop_f':'cmview_fcmview_f', 
                   'crfftmop_d':'cmview_dmview_d', 
                   'crfftmop_f':'cmview_fmview_f', 
                   'rcfftmop_d':'mview_dcmview_d', 
                   'rcfftmop_f':'mview_fcmview_f'}
    fftCreateDict={'ccfftip_f':'vsip_ccfftip_create_f(l[0],l[1],l[2],l[3],l[4])',
                     'ccfftop_f':'vsip_ccfftop_create_f(l[0],l[1],l[2],l[3],l[4])',
                     'rcfftop_f':'vsip_rcfftop_create_f(l[0],l[1],l[2],l[3])',
                     'crfftop_f':'vsip_crfftop_create_f(l[0],l[1],l[2],l[3])',
                     'ccfftip_d':'vsip_ccfftip_create_d(l[0],l[1],l[2],l[3],l[4])',
                     'ccfftop_d':'vsip_ccfftop_create_d(l[0],l[1],l[2],l[3],l[4])',
                     'rcfftop_d':'vsip_rcfftop_create_d(l[0],l[1],l[2],l[3])',
                     'crfftop_d':'vsip_crfftop_create_d(l[0],l[1],l[2],l[3])',
                     'ccfftmip_f':'vsip_ccfftmip_create_f(l[0],l[1],l[2],l[3],l[4],l[5],l[6])',
                     'ccfftmop_f':'vsip_ccfftmop_create_f(l[0],l[1],l[2],l[3],l[4],l[5],l[6])',
                     'rcfftmop_f':'vsip_rcfftmop_create_f(l[0],l[1],l[2],l[3],l[4],l[5])',
                     'crfftmop_f':'vsip_crfftmop_create_f(l[0],l[1],l[2],l[3],l[4],l[5])',
                     'ccfftmip_d':'vsip_ccfftmip_create_d(l[0],l[1],l[2],l[3],l[4],l[5],l[6])',
                     'ccfftmop_d':'vsip_ccfftmop_create_d(l[0],l[1],l[2],l[3],l[4],l[5],l[6])',
                     'rcfftmop_d':'vsip_rcfftmop_create_d(l[0],l[1],l[2],l[3],l[4],l[5])',
                     'crfftmop_d':'vsip_crfftmop_create_d(l[0],l[1],l[2],l[3],l[4],l[5])'}
    fftFuncDict={'cvview_d':'vsip_ccfftip_d(self.fft,l[0].view)',
                 'cvview_f':'vsip_ccfftip_f(self.fft,l[0].view)',
                 'cvview_dcvview_d':'vsip_ccfftop_d(self.fft,l[0].view,l[1].view)',
                 'cvview_fcvview_f':'vsip_ccfftop_d(self.fft,l[0].view,l[1].view)',
                 'vview_dcvview_d':'vsip_ccfftop_d(self.fft,l[0].view,l[1].view)',
                 'vview_fcvview_f':'vsip_ccfftop_d(self.fft,l[0].view,l[1].view)',
                 'cvview_dvview_d':'vsip_ccfftop_d(self.fft,l[0].view,l[1].view)',
                 'cvview_dvview_f':'vsip_ccfftop_d(self.fft,l[0].view,l[1].view)',
                 'cmview_d':'vsip_ccfftmip_d(self.fft,l[0].view)',
                 'cmview_f':'vsip_ccfftmip_d(self.fft,l[0].view)',
                 'cmview_dcmview_d':'vsip_ccfftmop_d(self.fft,l[0].view,l[1].view)'}             
    def __init__(self,t,arg):
        if FFT.fftCreateDict.has_key(t):
            self.__jvsip = JVSIP()
            self.__arg = arg
            self.__type = t
            l = arg
            self.__fft = eval(FFT.fftCreateDict[t])
        else:
            print("Type <:" + t + ":> not a recognized type for FFT")
    def __del__(self):
        del (self.__jvsip)
        vsip.destroy(self.__fft)
    def dft(self,arg):
        """This method requires a single view or two views enclosed in a tuple.
           Input success depends upon How the FFT object was created.
           Some error checking is done but it is not all inclusive.
        """
        l = arg
        if type(arg) != tuple:
            if 'pyJvsip.__View' in repr(arg):
                l=(arg,)
            else:
                print('Argument type must be a pyJvsip.__View or a tuple of two pyJvsip.__Views')
                return False
        chk = '__View' in repr(l[0])
        if chk:
            t = l[0].type
        if len(l) == 2:
            chk = chk and '__View' in repr(l[1])
            if chk:
                t = t + l[1].type
        if not chk:
            print('Argument must be a single view or a tuple of one or two views.')
            return False
        if FFT.fftFuncDict.has_key(t):
            eval(FFT.fftFuncDict[t])
            if len(l) == 2:
                return l[1]
            else:
                return l[0]
        else:
            print('Type <:' + t + ':> not a supported type for FFT')
            return False     
    @property
    def fft(self):
        return self.__fft
    @property
    def type(self):
        return self.__type
    @property
    def arg(self):
        return self.__arg
# Functions
def matrix(atype,cl,rl,major):
    """
       Convenience function to create a matrix. 
       Usage:
          m = matrix(atype, cl, rl, major)
       where
          atype is a string corresponding to a matrix view type:
             'mview_f', 'mview_d','cmview_f,'cmview_f','mview_i','mview_si','mview_uc'
             'mview_bl'
          cl is an integer corresponding to the matrix column length
          rl is an integer corresponding to the matrix row length
          major is a string indicating the major direction. The must be or contain
             'ROW'
            or 
             'COL'
    """
    f={'mview_f':'block_f',
       'mview_d':'block_d',
       'cmview_f':'cblock_f',
       'cmview_d':'cblock_d',
       'mview_i':'block_i',
       'mview_si':'block_si',
       'mview_uc':'block_uc',
       'mview_bl':'block_bl'}
    if f.has_key(atype):
        l=cl * rl;
        offset=0;
        if 'ROW' in major:
            row_stride=1
            col_stride=rl
        elif 'COL' in major:
            row_stride=cl
            col_stride=1
        else:
            print('major must be a string containing "ROW" or "COL"')
            return False
        return Block(f[atype],l).bind((offset,col_stride,cl,row_stride,rl))
        
    else:
        print('Type ' + atype + ' Not a valid type for matrix')
        return False

def vector(atype,length):
    """
       Convenience function to create a column vector. 
       Usage:
          v = vector(atype, length)
       where
          atype is a string corresponding to a matrix view type:
             'mview_f', 'mview_d','cmview_f,'cmview_f','mview_i','mview_si','mview_uc'
             'mview_bl'
          length is an integer corresponding to the vector length
    """
    f={'vview_f':'block_f',
       'vview_d':'block_d',
       'cvview_f':'cblock_f',
       'cvview_d':'cblock_d',
       'vview_i':'block_i',
       'vview_si':'block_si',
       'vview_uc':'block_uc',
       'vview_bl':'block_bl',
       'vview_vi':'block_vi',
       'vview_mi':'block_mi'}
    if f.has_key(atype):
        return Block(f[atype],length).bind((0,1,length))
    else:
        print('Type <:' + atype + ':> Not a valid type for vector')
        return False

def create(atype,atuple):
    """
       usage:
          anObject=create(aType,aTuple)
       where:
          aType corresponds to a valid type for the object being created and
          aTuple is a tuple corresponding to the argument list for aType
    """
    fftTypes = ['ccfftip_f', 'ccfftop_f', 'rcfftop_f', 'crfftop_f', 'ccfftip_d', 
                'ccfftop_d', 'rcfftop_d', 'crfftop_d', 'ccfftmip_f', 'ccfftmop_f', 
                'rcfftmop_f', 'crfftmop_f', 'ccfftmip_d', 'ccfftmop_d', 'rcfftmop_d', 
                 'crfftmop_d']
    if type(atuple) != tuple:
        args=(atuple,)
    else:
        args = atuple
    if atype in Block.vectorTypes:
        return vector(atype,args[0])
    elif atype in Block.matrixTypes:
        return matrix(atype,args[0],args[1],args[2])
    elif atype in fftTypes:
        return FFT(atype,args)
    elif 'rand' in atype:
        return Rand(args[0],args[1])
    else:
        print('Type <:' + atype + ':> not supported by pyVsip')
        return False

def copy(input,to):
    vsip.copy(input.view,to.view)
    return to