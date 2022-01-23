class NOC(record: String): Comparable<NOC> {
    val g: Int
    val s: Int
    val b: Int
    val name: String
    init {
        val tokens = record.split(" ")
        g = tokens.filter{ it != "" }[0].toInt()
        s = tokens.filter{ it != "" }[1].toInt()
        b = tokens.filter{ it != "" }[2].toInt()
        var num = 0
        var idx = 0
        while (num < 3) {
            if (tokens[idx++] != "") 
                num++
        }
        name = tokens.subList(idx, tokens.size).joinToString(" ")
    }
    override operator fun compareTo(other: NOC): Int {
        val o = other
        return (1004004*(o.g-g) + 1002*(o.s-s) + (o.b-b)).compareTo(0)
    }
}

fun main() {
    val n = readLine()!!.toInt()
    val nocs = (1..n).map{ NOC(readLine()!!) }
    println(nocs.minOrNull()!!.name)
}
