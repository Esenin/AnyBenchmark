#plot perfomance degradation
perf <- read.csv("bTreeTuning.csv")
perf <- perf[2:6]
pdf("bTree.pdf",width = 11 ,height = 5,family= "URWHelvetica", encoding="CP1251")
boxplot(perf, names=c(32, 64, 96, 128, 160), xlab="Page size", ylab="Perfomance")
dev.off()

