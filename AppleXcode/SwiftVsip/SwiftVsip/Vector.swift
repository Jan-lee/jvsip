//
//  Vector.swift
//  vsip
//
//  Created by Randall Judd on 4/22/16.
//  Copyright © 2016 RANDALL JUDD. All rights reserved.
//

import Foundation
import vsip
class Vector : View {
    var vsip: OpaquePointer?
    // vector bind
    func vBind(_ offset : vsip_index, stride : vsip_stride, length : vsip_length) -> OpaquePointer? {
        let blk = self.sBlock.vsip
        let t = self.sBlock.type
        switch t {
        case .f:
            return vsip_vbind_f(blk, offset, stride, length)
        case .d:
            return vsip_vbind_d(blk, offset, stride, length)
        case .cf:
            return vsip_cvbind_f(blk, offset, stride, length)
        case .cd:
            return vsip_cvbind_d(blk, offset, stride, length)
        case .i:
            return vsip_vbind_i(blk, offset, stride, length)
        case .li:
            return vsip_vbind_li(blk, offset, stride, length)
        case .si:
            return vsip_vbind_si(blk, offset, stride, length)
        case .uc:
            return vsip_vbind_uc(blk, offset, stride, length)
        case .vi:
            return vsip_vbind_vi(blk, offset, stride, length)
        case .mi:
            return vsip_vbind_mi(blk, offset, stride, length)
        case .bl:
            return vsip_vbind_bl(blk, offset, stride, length)
        }
    }
    init(block: Block, offset: vsip_offset, stride: vsip_stride, length: vsip_length){
        super.init(block: block, shape: "vector")
        self.vsip = self.vBind(offset, stride: stride, length: length)
    }
    // vector create
    convenience init(length : vsip_length, type : String){
        let blk = Block(length: length, type: type)
        self.init(block: blk, offset: 0, stride: 1, length: length)
    }
    convenience init(length : vsip_length, type : Block.Types){
        let blk = Block(length: length, type: type)
        self.init(block: blk, offset: 0, stride: 1, length: length)
    }
    // create view to hold derived subview
    init(block: Block, cView: OpaquePointer){
        super.init(block: block, shape: "vector")
        self.vsip = cView
    }
    deinit{
        let t = self.sBlock.type
        let id = self.myId.int32Value
        switch t {
        case .f:
            vsip_vdestroy_f(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_f id \(id)")
            }
        case .d:
            vsip_vdestroy_d(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_d id \(id)")
            }
        case .cf:
            vsip_cvdestroy_f(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("cvdestroy_f id \(id)")
            }
        case .cd:
            vsip_cvdestroy_d(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("cvdestroy_d id \(id)")
            }
        case .i:
            vsip_vdestroy_i(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_i id \(id)")
            }
        case .li:
            vsip_vdestroy_li(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_li id \(id)")
            }
        case .si:
            vsip_vdestroy_si(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_si id \(id)")
            }
        case .uc:
            vsip_vdestroy_uc(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_uc id \(id)")
            }
        case .vi:
            vsip_vdestroy_vi(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_vi id \(id)")
            }
        case .mi:
            vsip_vdestroy_mi(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_mi id \(id)")
            }
        case .bl:
            vsip_vdestroy_bl(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_bl id \(id)")
            }
        }
    }
    // MARK: Attributes
    var offset: vsip_offset {
        get{
            switch self.type {
            case .f :
                return vsip_vgetoffset_f(self.vsip!)
            case .d :
                return vsip_vgetoffset_d(self.vsip!)
            case .cf :
                return vsip_cvgetoffset_f(self.vsip!)
            case .cd :
                return vsip_cvgetoffset_d(self.vsip!)
            case .si :
                return vsip_vgetoffset_si(self.vsip!)
            case .i :
                return vsip_vgetoffset_i(self.vsip!)
            case .li :
                return vsip_vgetoffset_li(self.vsip!)
            case .uc :
                return vsip_vgetoffset_uc(self.vsip!)
            case .vi :
                return vsip_vgetoffset_vi(self.vsip!)
            case .mi :
                return vsip_vgetoffset_mi(self.vsip!)
            case .bl :
                return vsip_vgetoffset_bl(self.vsip!)
            }
        }
        set(offset){
            switch self.type {
            case .f :
                vsip_vputoffset_f(self.vsip!, offset)
            case .d :
                vsip_vputoffset_d(self.vsip!, offset)
            case .cf :
                vsip_cvputoffset_f(self.vsip!, offset)
            case .cd :
                vsip_cvputoffset_d(self.vsip!, offset)
            case .si :
                vsip_vputoffset_si(self.vsip!, offset)
            case .i :
                vsip_vputoffset_i(self.vsip!, offset)
            case .li :
                vsip_vputoffset_li(self.vsip!, offset)
            case .uc :
                vsip_vputoffset_uc(self.vsip!, offset)
            case .mi :
                vsip_vputoffset_mi(self.vsip!, offset)
            case .vi :
                vsip_vputoffset_vi(self.vsip!, offset)
            case .bl :
                vsip_vputoffset_bl(self.vsip!, offset)
            }
        }
    }
    var stride: vsip_stride {
        get{
            switch self.type {
            case .f :
                return vsip_vgetstride_f(self.vsip!)
            case .d :
                return vsip_vgetstride_d(self.vsip!)
            case .cf :
                return vsip_cvgetstride_f(self.vsip!)
            case .cd :
                return vsip_cvgetstride_d(self.vsip!)
            case .si :
                return vsip_vgetstride_si(self.vsip!)
            case .i :
                return vsip_vgetstride_i(self.vsip!)
            case .li :
                return vsip_vgetstride_li(self.vsip!)
            case .uc :
                return vsip_vgetstride_uc(self.vsip!)
            case .vi :
                return vsip_vgetstride_vi(self.vsip!)
            case .mi :
                return vsip_vgetstride_mi(self.vsip!)
            case .bl :
                return vsip_vgetstride_bl(self.vsip!)
            }
        }
        set(stride){
            switch self.type {
            case .f :
                vsip_vputstride_f(self.vsip!, stride)
            case .d :
                vsip_vputstride_d(self.vsip!, stride)
            case .cf :
                vsip_cvputstride_f(self.vsip!, stride)
            case .cd :
                vsip_cvputstride_d(self.vsip!, stride)
            case .si :
                vsip_vputstride_si(self.vsip!, stride)
            case .i :
                vsip_vputstride_i(self.vsip!, stride)
            case .li :
                vsip_vputstride_li(self.vsip!, stride)
            case .uc :
                vsip_vputstride_uc(self.vsip!, stride)
            case .mi :
                vsip_vputstride_mi(self.vsip!, stride)
            case .vi :
                vsip_vputstride_vi(self.vsip!, stride)
            case .bl :
                vsip_vputstride_bl(self.vsip!, stride)
            }
        }
    }
    var length: vsip_length {
        get{
            switch self.type {
            case .f :
                return vsip_vgetlength_f(self.vsip!)
            case .d :
                return vsip_vgetlength_d(self.vsip!)
            case .cf :
                return vsip_cvgetlength_f(self.vsip!)
            case .cd :
                return vsip_cvgetlength_d(self.vsip!)
            case .si :
                return vsip_vgetlength_si(self.vsip!)
            case .i :
                return vsip_vgetlength_i(self.vsip!)
            case .li :
                return vsip_vgetlength_li(self.vsip!)
            case .uc :
                return vsip_vgetlength_uc(self.vsip!)
            case .vi :
                return vsip_vgetlength_vi(self.vsip!)
            case .mi :
                return vsip_vgetlength_mi(self.vsip!)
            case .bl :
                return vsip_vgetlength_bl(self.vsip!)
            }
        }
        set(length){
            switch self.type {
            case .f :
                vsip_vputlength_f(self.vsip!, length)
            case .d :
                vsip_vputlength_d(self.vsip!, length)
            case .cf :
                vsip_cvputlength_f(self.vsip!, length)
            case .cd :
                vsip_cvputlength_d(self.vsip!, length)
            case .si :
                vsip_vputlength_si(self.vsip!, length)
            case .i :
                vsip_vputlength_i(self.vsip!, length)
            case .li :
                vsip_vputlength_li(self.vsip!, length)
            case .uc :
                vsip_vputlength_uc(self.vsip!, length)
            case .mi :
                vsip_vputlength_mi(self.vsip!, length)
            case .vi :
                vsip_vputlength_vi(self.vsip!, length)
            case .bl :
                vsip_vputlength_bl(self.vsip!, length)
            }
        }
    }
    // MARK: sub views
    var real: Vector{
        get{
            let ans = super.real(self.vsip!) // C VSIP real view
            let blk = ans.0!
            let v = ans.1!
            return Vector(block: blk, cView: v)
            
        }
    }
    var imag: Vector{
        get{
            let ans = super.imag(self.vsip!) // C VSIP imag view
            let blk = ans.0!
            let v = ans.1!
            return Vector(block: blk, cView: v)
            
        }
    }
    // vector subscript operator
    subscript(index: vsip_index) -> (Block.Types?, NSNumber?, NSNumber?) {
        get{
            return super.get(self.vsip!, index: index)
        }
        set(value){
            super.put(self.vsip!, index: index, value: value)
        }
    }
    subscript() -> (Block.Types?, NSNumber?, NSNumber?){
        get{
            return self[0]
        }
        set(value){
            self.fill(value)
        }
    }
    // MARK: data generators
    func ramp(_ start : NSNumber, increment : NSNumber) -> Vector {
        switch self.type {
        case .d:
            vsip_vramp_d(start.doubleValue, increment.doubleValue, self.vsip!)
        case .f:
            vsip_vramp_f(start.floatValue, increment.floatValue, self.vsip!)
        case .i:
            vsip_vramp_i(start.int32Value, increment.int32Value, self.vsip!)
        case .si:
            vsip_vramp_si(start.int16Value, increment.int16Value, self.vsip!)
        case .uc:
            vsip_vramp_uc(start.uint8Value, increment.uint8Value, self.vsip!)
        case .vi:
            vsip_vramp_vi(start.uintValue, increment.uintValue, self.vsip!)
        default:
            print("Type " + self.type.rawValue + " not supported for ramp")
        }
        return self
    }
    func ramp(_ start : Double, increment : Double) -> Vector {
        let s = NSNumber( value: start)
        let i = NSNumber( value: increment)
        return ramp(s, increment: i)
    }
    func ramp(_ start : Float, increment : Float) -> Vector {
        let s = NSNumber( value: start)
        let i = NSNumber( value: increment)
        return ramp(s, increment: i)
    }

    func ramp(_ start : Int, increment : Int) -> Vector {
        let s = NSNumber( value: start)
        let i = NSNumber( value: increment)
        return ramp(s, increment: i)
    }
    
    func ramp(_ start : UInt, increment : UInt) -> Vector {
        let s = NSNumber( value: start)
        let i = NSNumber( value: increment)
        return ramp(s, increment: i)
    }
    func ramp(_ start : vsip_scalar_si, increment : vsip_scalar_si) -> Vector {
        let s = NSNumber( value: start)
        let i = NSNumber( value: increment)
        return ramp(s, increment: i)
    }
    func ramp(_ start : UInt8, increment : UInt8) -> Vector {
        let s = NSNumber( value: start)
        let i = NSNumber( value: increment)
        return ramp(s, increment: i)
    }
    func fill(_ value: (Block.Types?, NSNumber?,  NSNumber?)){
        switch self.type{
        case .d:
            vsip_vfill_d(value.1!.doubleValue,self.vsip!)
        case .f:
            vsip_vfill_f(value.1!.floatValue,self.vsip!)
        case .cd:
            vsip_cvfill_d(vsip_cmplx_d(value.1!.doubleValue,value.2!.doubleValue),self.vsip!)
        case .cf:
            vsip_cvfill_f(vsip_cmplx_f(value.1!.floatValue,value.2!.floatValue),self.vsip!)
        case .vi:
            vsip_vfill_vi(value.1!.uintValue,self.vsip!)
        case .i:
            vsip_vfill_i(value.1!.int32Value,self.vsip!)
        case .li:
            vsip_vfill_li(value.1!.intValue,self.vsip!)
        case .si:
            vsip_vfill_si(value.1!.int16Value,self.vsip!)
        case .uc:
            vsip_vfill_uc(value.1!.uint8Value,self.vsip!)
        default:
            break
        }
    }
    func fill(_ value: NSNumber){
        switch self.type{
        case .d:
            vsip_vfill_d(value.doubleValue,self.vsip!)
        case .f:
            vsip_vfill_f(value.floatValue,self.vsip!)
        case .cd:
            vsip_cvfill_d(vsip_cmplx_d(value.doubleValue,0.0),self.vsip!)
        case .cf:
            vsip_cvfill_f(vsip_cmplx_f(value.floatValue,0.0),self.vsip!)
        case .vi:
            vsip_vfill_vi(value.uintValue,self.vsip!)
        case .i:
            vsip_vfill_i(value.int32Value,self.vsip!)
        case .li:
            vsip_vfill_li(value.intValue,self.vsip!)
        case .si:
            vsip_vfill_si(value.int16Value,self.vsip!)
        case .uc:
            vsip_vfill_uc(value.uint8Value,self.vsip!)
        default:
            break
        }
    }
    func fill(_ value: vsip_cscalar_d){
        self.fill((Block.Types.cd, NSNumber(value: value.r), NSNumber(value: value.i)))
    }
    func fill(_ value: vsip_cscalar_f){
        self.fill((Block.Types.cd, NSNumber(value: value.r), NSNumber(value: value.i)))
    }
    func randn(_ seed: vsip_index, portable: Bool) -> Vector {
        let state = Rand(seed: seed, portable: portable)
        state.randn(self)
        return self
    }
    func randn(_ seed: vsip_index) -> Vector {
        return self.randn(seed, portable: true)
    }
    func randu(_ seed: vsip_index, portable: Bool) -> Vector{
        let state = Rand(seed: seed, portable: portable)
        state.randu(self)
        return self
    }
    func randu(_ seed: vsip_index) -> Vector {
        return self.randu(seed, portable: true)
    }
    // create empty vector of same type and view size. New data space created
    var empty: Vector?{
        return Vector(length: self.length, type: self.type.rawValue)
    }
    func empty(_ type: String) -> Vector{
        return Vector(length: self.length, type: type)
    }
    var copy: Vector? {
        let view = self.empty
        assert(view != nil, "Allocation Error")
        switch view!.type{
        case .f:
            vsip_vcopy_f_f(self.vsip!,view!.vsip!)
        case .d:
            vsip_vcopy_d_d(self.vsip!, view!.vsip!)
        case .cf:
            vsip_cvcopy_f_f(self.vsip!,view!.vsip!)
        case .cd:
            vsip_cvcopy_d_d(self.vsip!, view!.vsip!)
        case .i:
            vsip_vcopy_i_i(self.vsip!,view!.vsip!)
        case .si:
            vsip_vcopy_si_si(self.vsip!, view!.vsip!)
        case .vi:
            vsip_vcopy_vi_vi(self.vsip!,view!.vsip!)
        case .mi:
            vsip_vcopy_mi_mi(self.vsip!, view!.vsip!)
        default:
            break
        }
        return view
    }
    func copy(_ output: Vector) -> Vector{
        let t1 = self.type.rawValue
        let t2 = output.type.rawValue
        let t = t1+t2
        switch t{
        case "ff":
            vsip_vcopy_f_f(self.vsip!,output.vsip!)
        case "fcf":
            let r = output.real;let i = output.real
            vsip_vcopy_f_f(self.vsip!,r.vsip!)
            vsip_vfill_f(0.0,i.vsip!)
        case "dd":
            vsip_vcopy_d_d(self.vsip!,output.vsip!)
        case "dcd":
            let r = output.real;let i = output.real
            vsip_vcopy_d_d(self.vsip!,r.vsip!)
            vsip_vfill_d(0.0,i.vsip!)
        case "df":
            vsip_vcopy_d_f(self.vsip!,output.vsip!)
        case "fd":
            vsip_vcopy_f_d(self.vsip!,output.vsip!)
        case "if":
            vsip_vcopy_i_f(self.vsip!,output.vsip!)
        case "id":
            vsip_vcopy_i_d(self.vsip!, output.vsip!)
        case "ii":
            vsip_vcopy_i_i(self.vsip!, output.vsip!)
        case "iuc":
            vsip_vcopy_i_uc(self.vsip!, output.vsip!)
        case "ivi":
            vsip_vcopy_i_vi(self.vsip!, output.vsip!)
        case "sisi":
            vsip_vcopy_si_si(self.vsip!, output.vsip!)
        case "sid":
            vsip_vcopy_si_d(self.vsip!, output.vsip!)
        case "sif":
            vsip_vcopy_si_f(self.vsip!, output.vsip!)
        case "vivi":
            vsip_vcopy_vi_vi(self.vsip!, output.vsip!)
        case "vii":
            vsip_vcopy_vi_i(self.vsip!, output.vsip!)
        case "vid":
            vsip_vcopy_vi_d(self.vsip!, output.vsip!)
        case "vif":
            vsip_vcopy_i_f(self.vsip!, output.vsip!)
        default:
            break
        }
        return output
    }
    var clone: Vector? {
        return Vector(block: self.sBlock, offset: self.offset, stride: self.stride, length: self.length)
    }
    // MARK: Print
    func mString(_ format: String) -> String {
        let fmt = formatFmt(format)
        var retval = ""
        let n = self.length - 1
        for i in 0...n{
            retval += (i == 0) ? "[" : " "
            retval += super.scalarString(fmt, value: self[i])
            retval += (i == n) ?  "]\n" : ";\n"
        }
        return retval
    }
    func mPrint(_ format: String){
        let m = mString(format)
        print(m)
    }
    // MARK: Elementary Functions
    func acos(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vacos_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vacos_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out
    }
    func asin(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vasin_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vasin_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out
    }
    func atan(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vatan_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vatan_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out
    }
    func cos(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vcos_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vcos_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out
    }
    func sin(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vasin_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vasin_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out
    }
    func tan(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vtan_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vtan_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out
    }
    func exp(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vexp_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vexp_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out
    }
    func exp10(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vexp10_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vexp10_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out
    }
    func log(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vlog_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vlog_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out    }
    func log10(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vlog10_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vlog10_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out    }
    
    // MARK: Binary Functions
    func add(_ to: Vector, resultIn: Vector) -> Vector{
        switch self.type{
        case .f:
            vsip_vadd_f(self.vsip!, to.vsip!, resultIn.vsip!)
        case .d:
            vsip_vadd_d(self.vsip!, to.vsip!, resultIn.vsip!)
        case .cf:
            vsip_cvadd_f(self.vsip!, to.vsip!, resultIn.vsip!)
        case .cd:
            vsip_cvadd_d(self.vsip!, to.vsip!, resultIn.vsip!)
        case .si:
            vsip_vadd_si(self.vsip!, to.vsip!, resultIn.vsip!)
        case .i:
            vsip_vadd_i(self.vsip!, to.vsip!, resultIn.vsip!)
        case .li:
            vsip_vadd_li(self.vsip!, to.vsip!, resultIn.vsip!)
        case .uc:
            vsip_vadd_uc(self.vsip!, to.vsip!, resultIn.vsip!)
        case .vi:
            vsip_vadd_vi(self.vsip!, to.vsip!, resultIn.vsip!)
        default:
            break
        }
        return resultIn
    }
    func sub(_ from: Vector, resultIn: Vector) -> Vector{
        switch self.type{
        case .f:
            vsip_vsub_f(self.vsip!, from.vsip!, resultIn.vsip!)
        case .d:
            vsip_vadd_d(self.vsip!, from.vsip!, resultIn.vsip!)
        case .cf:
            vsip_cvsub_f(self.vsip!, from.vsip!, resultIn.vsip!)
        case .cd:
            vsip_cvsub_d(self.vsip!, from.vsip!, resultIn.vsip!)
        case .si:
            vsip_vsub_si(self.vsip!, from.vsip!, resultIn.vsip!)
        case .i:
            vsip_vsub_i(self.vsip!, from.vsip!, resultIn.vsip!)
        case .uc:
            vsip_vsub_uc(self.vsip!, from.vsip!, resultIn.vsip!)
        default:
            break
        }
        return resultIn
    }
}

   
